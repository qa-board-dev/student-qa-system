//
// Created by axelpc on 2/11/2026.
//

#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include "ReviewerWindow.h"

#include <qmessagebox.h>

ReviewerWindow::ReviewerWindow(PostManager &pm, QWidget *parent)
    :QMainWindow(parent) , postManager(pm) //
{

    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Reviewer Dashboard");
    title->setAlignment(Qt::AlignCenter);

    QListWidget *answersToReview = new QListWidget;

    reviewBox = new QTextEdit(this);//
    reviewBox->setPlaceholderText("Write your review here: ");

    QPushButton *submitReview = new QPushButton("Submit Review");
    QPushButton *logoutBtn = new QPushButton("Logout");
    QPushButton *ShowPosts = new QPushButton("Show Posts"); //


    layout->addWidget(title);
    layout->addWidget(new QLabel("Answers:"));
    layout->addWidget(answersToReview);
    layout->addWidget(new QLabel("Review:"));
    layout->addWidget(reviewBox);
    layout->addWidget(submitReview);
    layout->addWidget(ShowPosts);
    layout->addWidget(logoutBtn);

    setCentralWidget(widget);

    connect(ShowPosts, &QPushButton::clicked, this, &ReviewerWindow::onShowPostsClicked);
    connect(logoutBtn, &QPushButton::clicked, this, &QWidget::close);

}
void ReviewerWindow::onShowPostsClicked() {
    //qDebug() << "ShowPosts clicked!";
    //if (!reviewBox) {
       // qDebug()<< "reviewBox is null!";
        //return;
    //}
    // reviewBox->clear();

    const auto &posts = postManager.getPost();
    if (posts.size()==0) {
        QMessageBox::information(this,"Error","No posts available");
    }
    //qDebug()<<"Number of posts:" << posts.size();
    for (const Post &p : posts) {
        QString postText;
        postText += "Author: " + QString::fromStdString(p.getAuthor()) + "\n";
        postText += "Content: " + QString::fromStdString(p.getContent()) + "\n";
      reviewBox->append(postText);
    }
}