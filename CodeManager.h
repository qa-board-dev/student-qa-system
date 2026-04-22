//
// Created by Luka Powers on 4/21/26.
//

#ifndef CODEMANAGER_H
#define CODEMANAGER_H
#include <QDate>
#include <QNetworkAccessManager>
#include <QString>
#include <QObject>


struct InviteCode {
    QString code;
    QDate expiration;
    QString status; // mark code "used" or "unused"
};

class CodeManager : public QObject {
    Q_OBJECT

public:
    explicit CodeManager(QObject *parent = nullptr);
    bool isValid(const QString& code);
    void markUsed(const QString& code);
    QString generate(const QDate& expiration);
    void save();
    void load();

private:
    std::vector<InviteCode> codes;
    QString firebaseURL = "https://cse360-qa-default-rtdb.firebaseio.com/codes.json";
    QNetworkAccessManager *networkManager;
};

#endif //CODEMANAGER_H
