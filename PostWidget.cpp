//
// Created by 16198 on 4/1/2026.
//
#include "PostWidget.h"

PostWidget::PostWidget(const QString &author,const QString &content, QWidget *parent): QWidget(parent), likes(0), dislikes(0) {
    authorLabel = new QLabel("Author: "+ author);
    authorLabel->setStyleSheet("font-weight:bold;"
        );
    questionLabel = new QLabel("Question:\n");
    questionLabel->setStyleSheet("font-weight:bold;"
        );
    contentLabel = new QLabel(content);
    contentLabel->setWordWrap(true);

    likeButton = new QPushButton("\U0001F44D 0");
    dislikeButton = new QPushButton("\U0001F44E 0");
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
        likes++;
        likeButton->setText("\U0001F44D" + QString::number(likes));
    }
void PostWidget::handleDislike(){
    dislikes++;
    dislikeButton->setText("\U0001F44E" + QString::number(dislikes));
}









