//
// Created by 16198 on 2/25/2026.
//

#ifndef USER_UI_POST_H
#define USER_UI_POST_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <QString>
#include <QStringList>

using namespace std;


class Post {
private:
    QString author; // QString change
    QString content; // QString change
    bool approved;
    QStringList keywords;
    void generateKeywords();
public:
    Post(const QString& author, const QString &content); // QString change
    QString getAuthor() const; //QString change
    QString getContent() const; // QString change
    bool isApproved() const;
    void approve();
    QStringList getKeywords() const;
};


#endif //USER_UI_DISCUSSIONBOARDTEST_H