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

StudentWindow::StudentWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Student Dashboard");
    title->setAlignment(Qt::AlignCenter);

    QTextEdit *questionBox = new QTextEdit;
    questionBox->setPlaceholderText("Ask your question here: ");

    QListWidget *relatedQuestions = new QListWidget;

    QListWidget *answersList = new QListWidget;

    QPushButton *submitBtn = new QPushButton("Submit Question");
    QPushButton *logoutBtn = new QPushButton("Logout");

    layout->addWidget(title);
    layout->addWidget(new QLabel("Your Question:"));
    layout->addWidget(questionBox);
    layout->addWidget(new QLabel("Related Questions:"));
    layout->addWidget(relatedQuestions);
    layout->addWidget(answersList);
    layout->addWidget(submitBtn);
    layout->addWidget(logoutBtn);

    setCentralWidget(widget);

    connect(logoutBtn, &QPushButton::clicked, this, &QWidget::close);

}
