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
#include "PostWidget.h"
#include "MainWindow.h"
#include <QComboBox>

ReviewerWindow::ReviewerWindow(PostManager &pm,MainWindow* parentMain, QWidget *parent)
    :QMainWindow(parent) , postManager(pm), mainWindow(parentMain) //
{
    resize(900, 600);
//qDebug() << "displayPosts called";
    QWidget *widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setStyleSheet("background-color: #d3d3d3;");
    QComboBox *filterBox = new QComboBox;
    filterBox->setStyleSheet(R"(
        QComboBox {
        background-color: #ffffff;
        border: 1px solid #dcdcdc;
        border-radius: 8px;
        padding: 6px 12px;
        padding-right: 25px;
        font-size: 13px;
        color: #222;
        }
        QComboBox:hover {
      border: 1px solid #999
      }

       QComboBox::drop-down {
        sub-control-origin: padding
        sub-control-position: top right;
        width: 20px;
        border: none;
        width: 20px;
       }
      QComboBox::down-arrow {
      image: none;
      border-left: 5px solid transparency;
      border-right: 6px solid #555;
      border-top: 6px solid #555;
      margin-right: 8px;
}

       QComboBox QAbstractItemView {
        background-color: #ffffff;
        border: 1px solid #ddd;
        border-radius: 6px;
        selection-background-color: #f0f2f5;

       }
         )");
    filterBox->setEditable(true);
    filterBox->lineEdit()->setReadOnly(true);
    filterBox->addItems({"All Posts","UpVoted","DownVoted"});
    filterBox->setCurrentIndex(-1);
    filterBox->lineEdit()->setPlaceholderText("Options");

    mainLayout->addWidget(filterBox);

    postsLayout = new QVBoxLayout();
    mainLayout->addLayout(postsLayout);
    mainLayout->addStretch();
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    QPushButton *Previous = new QPushButton("Previous");
    QString pillstyle = "QPushButton {"
    " background-color: #3498db;"
    " color: white;"
    " border-radius: 20px;"
    " padding: 8px 16px;"
    " font-size: 14px;"
    "}"
    "QPushButton:hover {"
    " background-color:#1f618d;"
    "}";
    Previous->setStyleSheet((pillstyle));
    Previous->setFixedWidth((150));
    Previous->setFixedHeight((40));
    bottomLayout->addWidget(Previous);
    mainLayout->addLayout(bottomLayout);
    setCentralWidget((widget));
    //displayPosts();
    connect(filterBox, &QComboBox::currentTextChanged, this, &ReviewerWindow::onFilterChanged);
    connect(Previous, &QPushButton::clicked, this, &ReviewerWindow::handlePrevious);

}
void ReviewerWindow::onFilterChanged(const QString &text){
    displayPosts(text);
}
void ReviewerWindow::displayPosts(const QString &filter) {
    QLayoutItem *item;
    while ((item = postsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
   //qDebug() << "Post count: " << postManager.getPost().size();
    for (const Post &p : postManager.getPost()) {
        if (filter == "All Posts") {
            PostWidget *widget = new PostWidget(p.getAuthor(),p.getContent(),p.getAnswers());
            postsLayout->addWidget(widget);
        }
    }
}
void ReviewerWindow::handlePrevious() {
    if (mainWindow) {
        mainWindow->showRoleSelection();
    }
    this->hide();
}
/*
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
    reviewBox->clear();
    for (const Post &p : posts) {
        QString postText;
        postText += "Author: " + p.getAuthor() + "\n"; //QString change
        postText += "Content: " + p.getContent() + "\n"; //QString change
      reviewBox->append(postText);
    }
}
*/
