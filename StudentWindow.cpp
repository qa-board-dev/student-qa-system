//
// Created by axelpc on 2/11/2026.
//

#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include "StudentWindow.h"
#include <QLineEdit>
#include "MainWindow.h"
using namespace std;
#include <string>
#include "Post.h"
#include <QMessagebox.h>



StudentWindow::StudentWindow(PostManager &pm, MainWindow* parentMain, QWidget *parent)
    :QMainWindow(parent), postManager(pm), mainWindow(parentMain) {
    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Student Dashboard");
    title->setAlignment(Qt::AlignCenter);

    Author = new QLineEdit(this); //
    Author->setPlaceholderText(("Enter Name Here")); //

    questionBox = new QTextEdit(this);//
    questionBox->setPlaceholderText("Ask your question here: ");

    viewQuestionBox = new QListWidget(this);//


    QListWidget *relatedQuestions = new QListWidget;

    QListWidget *answersList = new QListWidget;

    QHBoxLayout *buttonlayout = new QHBoxLayout();

    QString pillshape = "QPushButton {"
    " background-color: #3498db;"
    " color: white;"
    " border-radius: 20px;"
    " padding: 8px 16px;"
    " font-size: 14px;"
    "}"
    "QPushButton:hover {"
    " background-color:#1f618d;"
    "}";


    QPushButton *submitBtn = new QPushButton("Submit Question");
    submitBtn->setFixedWidth((150));
    submitBtn->setFixedHeight((40));
    submitBtn->setStyleSheet(pillshape);

    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setFixedWidth((150));
    logoutBtn->setFixedHeight((40));
    logoutBtn->setStyleSheet(pillshape);




    QPushButton *ShowPosts = new QPushButton("Show Posts"); //
    ShowPosts->setFixedWidth((150));
    ShowPosts->setFixedHeight((40));
    ShowPosts->setStyleSheet(pillshape);

    QPushButton *Previous = new QPushButton("Previous"); //
    Previous->setFixedWidth((150));
    Previous->setFixedHeight((40));
    Previous->setStyleSheet(pillshape);

    buttonlayout->addWidget(submitBtn);
    buttonlayout->addSpacing(20);
    buttonlayout->addWidget(ShowPosts);
    buttonlayout->addSpacing(20);
    buttonlayout->addWidget(Previous);
    buttonlayout->addSpacing(20);
    buttonlayout->addWidget(logoutBtn);


    layout->addWidget(title);
    layout->addWidget(new QLabel("Author:"));
    layout->addWidget(Author); //
    layout->addWidget(new QLabel("Your Question:"));
    layout->addWidget(questionBox);
    layout->addWidget(new QLabel("Related Questions:"));
    layout->addWidget(relatedQuestions);
    layout->addWidget(new QLabel("Questions List:"));
    layout->addWidget(viewQuestionBox);
    layout->addWidget(new QLabel("Question Answers:"));
    layout->addWidget(answersList);
    layout->addLayout(buttonlayout);//

    setCentralWidget(widget);


    connect(ShowPosts, &QPushButton::clicked, this, &StudentWindow::onShowPostsclicked);
    connect(Previous, &QPushButton::clicked, this, &StudentWindow::handlePrevious);
    connect(submitBtn, &QPushButton::clicked,this, &StudentWindow::handleSubmit); //
    connect(logoutBtn, &QPushButton::clicked, this, &QWidget::close);

}
void StudentWindow::handleSubmit(){ //
    string author = Author->text().toStdString();
    string content = questionBox->toPlainText().toStdString();
    try {
        Post newPost(author, content);
        postManager.addPost(newPost);
        //qDebug << "Added post. Total Posts:
        Author->clear();
        questionBox->clear();
        QMessageBox::information(this, "Success", "Post Submitted!");
    }
    catch (invalid_argument&) {
        QMessageBox::information(this, "Error","One or more boxes is empty ");
    }
}

void StudentWindow::onShowPostsclicked() {
    //qDebug() << "ShowPosts clicked!";
    //if (!viewQuestionBox) {
       // qDebug()<< "reviewBox is null!";
       // return;
   // }
    // reviewBox->clear();
    const auto &posts = postManager.getPost();
    if (posts.size()==0) {
        QMessageBox::information(this,"Error","No posts available");
    }
    // qDebug()<<"Number of posts:" << posts.size();
    for (const Post &p : posts) {
        QString postText = QString::fromStdString(p.getAuthor())+": " + QString::fromStdString(p.getContent());

        viewQuestionBox->addItem(postText);
    }
}
void StudentWindow::handlePrevious() {
    if (mainWindow) {
        mainWindow->showRoleSelection();
    }
    this->hide();
}