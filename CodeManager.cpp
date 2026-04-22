//
// Created by Luka Powers on 4/21/26.
//

#include "CodeManager.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QRandomGenerator>

CodeManager::CodeManager(QObject *parent) : QObject(parent), networkManager(new QNetworkAccessManager(this)) {}


bool CodeManager::isValid(const QString& code) {
    for (const auto& invC : codes) {
        if (invC.code == code && QDate::currentDate() <= invC.expiration && invC.status == "unused") {
            return true;
        }
    }
    return false;
}

void CodeManager::markUsed(const QString& code) {
    for (auto& invC : codes) {
        if (invC.code == code) {
            invC.status = "used";
            save();
            return;
        }
    }
}

QString CodeManager::generate(const QDate& expiration) {
    int tmpCode;
    bool isUnique;

    do {
        tmpCode = QRandomGenerator::global()->bounded(1000,9999);
        isUnique = true;
        for (const auto& invC : codes) {
            if (invC.code == QString::number(tmpCode)) {
                isUnique = false;
                break;
            }
        }
    } while (!isUnique);

    InviteCode newCode;
    newCode.code = QString::number(tmpCode);
    newCode.expiration = expiration;
    newCode.status = "unused";
    codes.push_back(newCode);
    save();

    return newCode.code;
}

void CodeManager::save() {
    QJsonArray codeArray;

    for (const auto& invC : codes) {
        QJsonObject codeObject;
        codeObject["code"] = invC.code;
        codeObject["expiration"] = invC.expiration.toString("yyyy-MM-dd");
        codeObject["status"] = invC.status;
        codeArray.append(codeObject);
    }

    QJsonDocument doc(codeArray);
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

void CodeManager::load() {
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
    QJsonArray codeArray = doc.array();

    codes.clear();

    for (int i = 0; i < codeArray.size(); i++) {
        QJsonObject codeObject = codeArray.at(i).toObject();

        InviteCode inv;
        inv.code = codeObject["code"].toString();
        inv.expiration = QDate::fromString(codeObject["expiration"].toString(), "yyyy-MM-dd");
        inv.status = codeObject["status"].toString();

        codes.push_back(inv);
    }
}