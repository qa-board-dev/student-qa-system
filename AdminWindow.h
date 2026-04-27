//
// Created by axelpc on 2/11/2026.
//

#ifndef USER_UI_ADMINWINDOW_H
#define USER_UI_ADMINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "CodeManager.h"

class AdminWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit AdminWindow(CodeManager& cm, QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    CodeManager& codeManager;

signals:
    void logoutRequest();
    void backRequest();
};

#endif //USER_UI_ADMINWINDOW_H