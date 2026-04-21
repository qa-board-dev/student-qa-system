//
// Created by axel_ on 2/11/2026.
//


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "UserModel.h"
#include "PostManager.h"
#include "StudentWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void showRoleSelection();


private:
    QStackedWidget *stack;
    UserModel model;

    QWidget* createLoginScreen();
    QWidget* createFirstUserSetupScreen();
    QWidget* createRoleSelectionScreen();
    QWidget* createSignupScreen();
    bool isValidInviteCode(const QString& code);
    void setCodeUsed(const QString& code);

    PostManager postManager;//

    QString tempUsername;
    QString tempPassword;
    QString tempInviteCode;
    QString currentUsername;
    bool signupMode = false;

    void switchScreen(QWidget* screen);
};

#endif