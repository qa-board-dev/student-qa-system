//
// Created by 16198 on 4/1/2026.
//
#include "PostWidget.h"

PostWidget::PostWidget(const QString &author,const QString &content,const QVector<Answer> &answers, QWidget *parent): QWidget(parent), isLiked(false), isDisliked(false) {
    authorLabel = new QLabel("Author: "+ author);
    QFont authorFont;
    authorFont.setBold(true);
    authorFont.setPointSize(12);
    authorLabel->setFont(authorFont);

    questionLabel = new QLabel("Question:\n");
    QFont questionFont;
    questionFont.setBold(true);
    questionFont.setPointSize(12);
    questionLabel->setFont(questionFont);

    contentLabel = new QLabel(content);
    contentLabel->setWordWrap(true);

    likeButton = new QPushButton("\U0001F44D");
    dislikeButton = new QPushButton("\U0001F44E");
    likeButton->setFixedSize(60,25);
    dislikeButton->setFixedSize(60,25);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(likeButton);
    buttonLayout->addWidget(dislikeButton);
    buttonLayout->addStretch();

    layout->addWidget(authorLabel);
    layout->addWidget(questionLabel);
    layout->addWidget(contentLabel);
    for (const Answer &ans : answers) {
        QString text = "<b>Answer by " + ans.author + ":</b><br>" + ans.content;
        QLabel *answerLabel = new QLabel(text);
        answerLabel->setWordWrap(true);

        layout->addWidget(answerLabel);
    }

    layout->addLayout(buttonLayout);


    contentLabel->setStyleSheet(R"(background-color: #ffffff;
color: #222222;
border: 1px solid #ddd;
border-radius: 10px;
        )");

    dislikeButton->setStyleSheet(R"(background-color: #ffffff;
color: #222222;
border: 1px solid #ddd;
border-radius: 10px;
        )");
    likeButton->setStyleSheet(R"(background-color: #ffffff;
color: #222222;
border: 1px solid #ddd;
border-radius: 10px;
        )");

    connect(likeButton, &QPushButton::clicked, this, &PostWidget::handleLike);
    connect(dislikeButton, &QPushButton::clicked, this, &PostWidget::handleDislike);
}

    void PostWidget::handleLike(){
    isLiked = !isLiked;
    if (isLiked) {
            likeButton->setStyleSheet("background-color: green; color:white;");
        dislikeButton->setEnabled(false);
        }
    else {
        likeButton->setStyleSheet("");
        dislikeButton->setEnabled(true);
    }
    }
void PostWidget::handleDislike(){
    isDisliked = !isDisliked;
    if (isDisliked) {
        dislikeButton->setStyleSheet("background-color: green; color:white;");
        likeButton->setEnabled(false);
    }
    else {
        dislikeButton->setStyleSheet("");
        likeButton->setEnabled(true);
    }

}









