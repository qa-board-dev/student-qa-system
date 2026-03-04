//
// Created by Luka Powers on 2/27/26.
//

#include "UserModel.h"

#include <QFile>
#include <qjsonarray.h>
#include <qjsonobject.h>

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
    QByteArray bytes = doc.toJson();
    QFile file(filepath);
    file.open(QIODevice::WriteOnly);
    file.write(bytes);
    file.close();
}

void UserModel::load() {
    QFile file(filepath);

    if (!file.exists()) {
        //qDebug() << "File does not exist";
        return;
    }
    //qDebug() << "File loaded";

    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    QJsonArray userArray = doc.array();

    for (int i = 0; i < userArray.size(); i++) {
        QJsonObject userObject = userArray.at(i).toObject();
        QJsonArray roles = userObject["roles"].toArray();
        User u2;
        u2.username = userObject["username"].toString();
        u2.password = userObject["password"].toString();

        for (int j = 0; j < roles.size(); j++) {
            u2.roles.append(roles[j].toString());
        }

        users.push_back(u2);
    }

    //qDebug() << "users: " << users.size();

}

