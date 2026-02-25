//
// Created by axelpc on 2/11/2026.
//
#include "AdminWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QMainWindow>


AdminWindow::AdminWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Admin Dashboard");
    title->setAlignment(Qt::AlignCenter);

    QLineEdit *inviteCode = new QLineEdit;
    inviteCode->setPlaceholderText("One-time Invitation Code");

    QDateEdit *deadline = new QDateEdit;
    deadline->setCalendarPopup(true);

    QPushButton *generateBtn = new QPushButton("Generate Invitation");
    QPushButton *logoutBtn = new QPushButton("Logout");

    layout->addWidget(title);
    layout->addWidget(inviteCode);
    layout->addWidget(deadline);
    layout->addWidget(generateBtn);
    layout->addWidget(logoutBtn);

    setCentralWidget(widget);

    connect(logoutBtn, &QPushButton::clicked, this, &QWidget::close);

}