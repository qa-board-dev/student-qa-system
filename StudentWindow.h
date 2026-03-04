//
// Created by axelpc on 2/11/2026.
//

#ifndef USER_UI_STUDENTWINDOW_H
#define USER_UI_STUDENTWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget> //
#include <QLineEdit> //
#include <QTextEdit> //


class StudentWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    QLineEdit *Author; //
    QTextEdit *questionBox; //

private slots: //
    void handleSubmit(); //
    void handlePrevious(); //
};
#endif //USER_UI_STUDENTWINDOW_H