//
// Created by Luka Powers on 3/3/26.
//

#ifndef USERMODEL_H
#define USERMODEL_H
#include <string>
#include <QString>
#include <QStringList>

struct User {
    QString username;
    QString password;
    QStringList roles;
};

class UserModel {
public:
    bool addUser(QString username, QString password, QStringList roles);
    bool authenticate(QString username, QString password);
    QStringList getRoles(QString username);
    bool firstUser();
    void save();
    void load();

private:
    std::vector<User> users;
    QString filepath = "userList.json";
};



#endif //USERMODEL_H
