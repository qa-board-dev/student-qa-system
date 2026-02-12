//
// Created by axelpc on 2/11/2026.
//

#include <QLabel>
#include <qlistwidget.h>
#include <QPushButton>
#include <qtextedit.h>
#include <QVBoxLayout>
#include <QWidget>
#include "ReviewerWindow.h"

ReviewerWindow::ReviewerWindow(QWidget *parent)
    :       QMainWindow(parent)
{

    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Reviewer Dashboard");
    title->setAlignment(Qt::AlignCenter);

    QListWidget *answersToReview = new QListWidget;

    QTextEdit *reviewBox = new QTextEdit;
    reviewBox->setPlaceholderText("Write your review here: ");

    QPushButton *submitReview = new QPushButton("Submit Review");
    QPushButton *logoutBtn = new QPushButton("Logout");

    layout->addWidget(title);
    layout->addWidget(new QLabel("Answers:"));
    layout->addWidget(answersToReview);
    layout->addWidget(new QLabel("Review:"));
    layout->addWidget(reviewBox);
    layout->addWidget(submitReview);
    layout->addWidget(logoutBtn);

    setCentralWidget(widget);

    connect(logoutBtn, &QPushButton::clicked, this, &QWidget::close);

}
