//
// Created by 16198 on 4/1/2026.
//
#ifndef PROJECT_A1_POSTWIDGET_H
#define PROJECT_A1_POSTWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include "Post.h"
class PostWidget : public QWidget {
    Q_OBJECT
public:
    explicit PostWidget(const QString &author, const QString &content,const QVector<Answer> &answers, QWidget *parent = nullptr);

private:
    QLabel *authorLabel;
    QLabel *contentLabel;
    QLabel *questionLabel;


    QPushButton *likeButton;
    QPushButton *dislikeButton;

    bool isLiked = false;
    bool isDisliked = false;
    private slots:
    void handleLike();
    void handleDislike();
};

#endif //PROJECT_A1_POSTWIDGET_H