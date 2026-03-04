//
// Created by axel_ on 2/11/2026.
//


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "UserModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    UserModel model;

    QWidget* createLoginScreen();
    QWidget* createFirstUserSetupScreen();
    QWidget* createRoleSelectionScreen();

    void switchScreen(QWidget* screen);
};

#endif