//
// Created by axel_ on 2/11/2026.
//

#include "MainWindow.h"
#include <QtWidgets>
#include <QSettings>
#include <QVBoxLayout>
#include <QFile>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stack = new QStackedWidget(this);
    setCentralWidget(stack);
    //setStyleSheet("background-color: white");



    stack->addWidget(createLoginScreen());
    stack->addWidget(createFirstUserSetupScreen());
    stack->addWidget(createRoleSelectionScreen());
    stack->addWidget(createAdminScreen());
    stack->addWidget(createStudentScreen());
    stack->addWidget(createReviewerScreen());

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

    connect(loginBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(2); // Role selection
    });

    connect(firstUserBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(1);
    });

    QSettings settings("MyCompany", "StudentQASystem");
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

    connect(createBtn, &QPushButton::clicked, [=](){
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

    connect(adminBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(3);
    });

    connect(studentBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(4);
    });

    connect(reviewerBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(5);
    });

    connect(logoutBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(0);
    });

    return widget;
}


QWidget* MainWindow::createAdminScreen()
{
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

    connect(logoutBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(0);
    });


    return widget;
}

QWidget* MainWindow::createStudentScreen()
{
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

    connect(logoutBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(0);
    });

    return widget;
}


QWidget* MainWindow::createReviewerScreen()
{
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

    connect(logoutBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(0);
    });

    return widget;
}
