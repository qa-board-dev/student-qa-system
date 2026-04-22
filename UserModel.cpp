//
// Created by Luka Powers on 2/27/26.
//

#include "UserModel.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

UserModel::UserModel(QObject *parent) : QObject(parent), networkManager(new QNetworkAccessManager(this)) {}

bool UserModel::addUser(QString username, QString password, QStringList roles) {
    for (const auto& user : users) {
        if (user.username == username) {
        return false;
        }
    }

    User u1;
    u1.username = username;
    u1.password = password;
    u1.roles = roles;

    users.push_back(u1);
    return true;
}

bool UserModel::authenticate(QString username, QString password) {
    //qDebug() << "trying" << username << ":" << password;
    for (const auto& user : users) {
        //qDebug() << "checking/trying" << user.username << ":" << user.password;
        if (user.username == username && user.password == password) {
            return true;
        }
    }

    return false;
}

QStringList UserModel::getRoles(QString username) {
    for (const auto& user : users) {
        if (user.username == username) {
            return user.roles;
        }
    }

    return {};
}

bool UserModel::firstUser() {
    return users.empty();
}

void UserModel::save() {
    QJsonArray userArray;

    for (const auto& user : users) {
        QJsonObject userObject;
        userObject["username"] = user.username;
        userObject["password"] = user.password;
        userObject["roles"] = QJsonArray::fromStringList(user.roles);
        userArray.append(userObject);
    }

    QJsonDocument doc(userArray);
    QUrl url(firebaseURL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->put(request, doc.toJson());

    connect(reply, &QNetworkReply::finished, this, [reply]() {
       if (reply->error() != QNetworkReply::NoError) {
          qWarning() << "Save failed: " << reply->errorString();
       }
       reply->deleteLater();
    });
}

void UserModel::load() {
    QUrl url(firebaseURL);
    QNetworkRequest request(url);

    QNetworkReply *reply = networkManager->get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "load failed: " << reply->errorString();
        reply->deleteLater();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonArray userArray = doc.array();

    users.clear();

    for (int i = 0; i < userArray.size(); i++) {
        QJsonObject userObject = userArray.at(i).toObject();

        User u2;
        u2.username = userObject["username"].toString();
        u2.password = userObject["password"].toString();

        QJsonArray roles = userObject["roles"].toArray();
        for (int j = 0; j < roles.size(); j++) {
            u2.roles.append(roles[j].toString());
        }

        users.push_back(u2);
    }

    //qDebug() << "users: " << users.size();

}

