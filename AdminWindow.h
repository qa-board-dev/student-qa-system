//
// Created by axelpc on 2/11/2026.
//

#ifndef USER_UI_ADMINWINDOW_H
#define USER_UI_ADMINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class AdminWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    QString generateInvitation(const QDate& expirationDate);

signals:
    void logoutRequest();
};

#endif //USER_UI_ADMINWINDOW_H