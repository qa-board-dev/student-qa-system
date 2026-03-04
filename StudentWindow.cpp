//
// Created by axelpc on 2/11/2026.
//

#include <QLabel>
#include <qlistwidget.h>
#include <QPushButton>
#include <qtextedit.h>
#include <QVBoxLayout>
#include <QWidget>
#include "StudentWindow.h"
#include <QLineEdit>
#include "MainWindow.h"
using namespace std;
#include <string>
#include "Post.h"
#include <QMessagebox.h>

StudentWindow::StudentWindow(QWidget *parent)
    :QMainWindow(parent) {
    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Student Dashboard");
    title->setAlignment(Qt::AlignCenter);

    Author = new QLineEdit(this); //
    Author->setPlaceholderText(("Enter Name Here")); //

    questionBox = new QTextEdit(this);//
    questionBox->setPlaceholderText("Ask your question here: ");

    QListWidget *relatedQuestions = new QListWidget;

    QListWidget *answersList = new QListWidget;

    QPushButton *submitBtn = new QPushButton("Submit Question");
    QPushButton *logoutBtn = new QPushButton("Logout");
    QPushButton *previousBtn = new QPushButton("Previous");


    layout->addWidget(title);
    layout->addWidget(new QLabel("Author:"));
    layout->addWidget(Author); //
    layout->addWidget(new QLabel("Your Question:"));
    layout->addWidget(questionBox);
    layout->addWidget(new QLabel("Related Questions:"));
    layout->addWidget(relatedQuestions);
    layout->addWidget(answersList);
    layout->addWidget(submitBtn);
    layout->addWidget(previousBtn);
    layout->addWidget(logoutBtn);

    setCentralWidget(widget);


    connect(previousBtn,&QPushButton::clicked, this, &StudentWindow::handlePrevious); //
    connect(submitBtn, &QPushButton::clicked,this, &StudentWindow::handleSubmit); //
    connect(logoutBtn, &QPushButton::clicked, this, &QWidget::close);

}
void StudentWindow::handleSubmit(){ //
    string author = Author->text().toStdString();
    string content = questionBox->toPlainText().toStdString();
    try {
        Post newPost(author, content);
        QMessageBox::information(this, "Success", "Post Submitted!");
    }
    catch (invalid_argument&) {
        QMessageBox::information(this, "Error","Boxes cannot be left empty");
    }
}
void StudentWindow::handlePrevious() { //
    MainWindow *newMain = new MainWindow();
    newMain->show();
    this->hide();
}