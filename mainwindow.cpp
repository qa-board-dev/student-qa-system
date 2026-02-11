//
// Created by Luka Powers on 2/8/26.
//
#include "mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Project A1");
    resize(600, 400);
    menuBar()->setNativeMenuBar(false);

    menu = menuBar()->addMenu(tr("&File"));
    settingsMenu = menuBar()->addMenu(tr("&Settings"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *quitAction = new QAction(tr("Quit"), this);
    menu->addAction(quitAction);
    connect(quitAction, &QAction::triggered, this, &QMainWindow::close);

    settingsMenu->addAction(new QAction(tr("Preferences"), this));
    helpMenu->addAction(new QAction(tr("About"), this));

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QHBoxLayout *username = new QHBoxLayout();
    QLabel *usernameLabel = new QLabel(tr("Username:"));
    QLineEdit *usernameField = new QLineEdit();

    usernameLabel->setStyleSheet("color: white; font-size: 24px;");
    username->addWidget(usernameLabel);
    usernameField->setStyleSheet("color: white;");
    username->addWidget(usernameField);
    layout->addLayout(username);

    QHBoxLayout *password = new QHBoxLayout();
    QLabel *passwordLabel = new QLabel(tr("Password:"));
    QLineEdit *passwordField = new QLineEdit();

    passwordLabel->setStyleSheet("color: white; font-size: 24px;");
    password->addWidget(passwordLabel);
    passwordField->setStyleSheet("color: white");
    password->addWidget(passwordField);
    layout->addLayout(password);

    QComboBox *roles = new QComboBox(centralWidget);
    roles->addItem("Student");
    roles->addItem("Admin");
    roles->addItem("Reviewer");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *buttonLabel = new QPushButton(tr("Sign in"));
    buttonLayout->addWidget(buttonLabel);
    layout->addLayout(buttonLayout);




}
