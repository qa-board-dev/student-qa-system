//
// Created by Luka Powers on 2/27/26.
//

#ifndef USERMODEL_H
#define USERMODEL_H
#include <string>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QNetworkAccessManager>

struct User {
    QString username;
    QString password;
    QStringList roles;
};

class UserModel : public QObject {
    Q_OBJECT

public:
    explicit UserModel(QObject *parent = nullptr);

    bool addUser(QString username, QString password, QStringList roles);
    bool authenticate(QString username, QString password);
    QStringList getRoles(QString username);
    bool firstUser();
    void save();
    void load();

private:
    std::vector<User> users;
    QString firebaseURL = "https://cse360-qa-default-rtdb.firebaseio.com/users.json";
    QNetworkAccessManager *networkManager;
};



#endif //USERMODEL_H
