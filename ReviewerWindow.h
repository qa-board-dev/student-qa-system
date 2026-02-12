//
// Created by axelpc on 2/11/2026.
//

#ifndef USER_UI_REVIEWERWINDOW_H
#define USER_UI_REVIEWERWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class ReviewerWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit ReviewerWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
};

#endif //USER_UI_REVIEWERWINDOW_H