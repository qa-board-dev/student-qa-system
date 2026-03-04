//
// Created by axel_ on 2/11/2026.
//

#include "MainWindow.h"
#include <QtWidgets>
#include <QSettings>
#include <QVBoxLayout>
#include <QFile>
#include <QApplication>
#include "AdminWindow.h"
#include "StudentWindow.h"
#include "ReviewerWindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(900,600); //
    stack = new QStackedWidget(this);
    setCentralWidget(stack);
    //setStyleSheet("background-color: white");



    stack->addWidget(createLoginScreen());
    stack->addWidget(createFirstUserSetupScreen());
    stack->addWidget(createRoleSelectionScreen());
    stack->setCurrentIndex(0);
}


void MainWindow::switchScreen(QWidget *screen)
{
    stack->setCurrentWidget(screen);
}

QWidget* MainWindow::createLoginScreen()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Student Q&A System - Login");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold;");

    QLineEdit *username = new QLineEdit;
    username->setPlaceholderText("Username");

    QLineEdit *password = new QLineEdit;
    password->setPlaceholderText("Password");
    password->setEchoMode(QLineEdit::Password);

    QPushButton *loginBtn = new QPushButton("Login");
    QPushButton *firstUserBtn = new QPushButton("First User Setup");

    layout->addWidget(title);
    layout->addWidget(username);
    layout->addWidget(password);
    layout->addWidget(loginBtn);
    layout->addWidget(firstUserBtn);

    connect(loginBtn, &QPushButton::clicked, this, [this](){
        stack->setCurrentIndex(2);
    });

    connect(firstUserBtn, &QPushButton::clicked, this, [this]() {
        stack->setCurrentIndex(1);
    });

    QSettings settings("Admin", "QA");
    bool adminExists = settings.value("adminCreated", false).toBool();

    if (adminExists) {
        firstUserBtn->hide();
    }

    return widget;
}


QWidget* MainWindow::createFirstUserSetupScreen()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("First User Setup (Admin)");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 18px; font-weight: bold;");

    QLineEdit *username = new QLineEdit;
    username->setPlaceholderText("Admin Username");

    QLineEdit *password = new QLineEdit;
    password->setPlaceholderText("Password");
    password->setEchoMode(QLineEdit::Password);

    QPushButton *createBtn = new QPushButton("Create Admin Account");


    layout->addWidget(title);
    layout->addWidget(username);
    layout->addWidget(password);
    layout->addWidget(createBtn);

    connect(createBtn, &QPushButton::clicked, this, [this](){

		QSettings settings("Admin", "QA");
		settings.setValue("AdminCreated", true);
        QMessageBox::information(this, "Success",
                                 "Admin created. Please login again.");
        stack->setCurrentIndex(0);
    });

    return widget;
}


QWidget* MainWindow::createRoleSelectionScreen()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Select Role");
    title->setAlignment(Qt::AlignCenter);

    QPushButton *adminBtn = new QPushButton("Admin");
    QPushButton *studentBtn = new QPushButton("Student");
    QPushButton *reviewerBtn = new QPushButton("Reviewer");
    QPushButton *logoutBtn = new QPushButton("Logout");

    layout->addWidget(title);
    layout->addWidget(adminBtn);
    layout->addWidget(studentBtn);
    layout->addWidget(reviewerBtn);
    layout->addWidget(logoutBtn);

    connect(adminBtn, &QPushButton::clicked, this, [this]() {
        AdminWindow *admin = new AdminWindow();
		admin->show();

		this->hide();
    });

    connect(studentBtn, &QPushButton::clicked, this, [this]() {
        StudentWindow *student = new StudentWindow; //1
        student->show(); //1
        this->hide(); // 1
        stack->setCurrentIndex(4);
    });

    connect(reviewerBtn, &QPushButton::clicked, this, [this]() {
    ReviewerWindow *reviewer = new ReviewerWindow(this);
    reviewer->show();
    this->hide();
	});

connect(logoutBtn, &QPushButton::clicked, this, [this]() {
    stack->setCurrentIndex(0);
	});

    return widget;
}
