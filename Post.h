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

struct Answer {
    QString author;
    QString content;
    bool approved = false;
    bool isReviewer = false;
};

class Post {
private:
    QString author; // QString change
    QString content; // QString change
    QString reviewerFeedback;
    QVector<Answer> answers;
    bool approved;
    QStringList keywords;
    void generateKeywords();
    void setReviewerFeedback();
    QString getReviewerFeedback() const;
public:
    Post(const QString& author, const QString &content); // QString change
    QString getAuthor() const; //QString change
    QString getContent() const; // QString change
    bool isApproved() const;
    void approve();
    QStringList getKeywords() const;
    void addAnswer(const Answer& answer);
    QVector<Answer> getAnswers() const;

};



#endif //USER_UI_DISCUSSIONBOARDTEST_H