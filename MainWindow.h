//
// Created by axel_ on 2/11/2026.
//


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;

    QWidget* createLoginScreen();
    QWidget* createFirstUserSetupScreen();
    QWidget* createRoleSelectionScreen();

    void switchScreen(QWidget* screen);
};

#endif