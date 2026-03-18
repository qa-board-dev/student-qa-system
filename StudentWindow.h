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
#include "PostManager.h"
#include <QListWidget>


class MainWindow; //

class StudentWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit StudentWindow(PostManager &pm, MainWindow* parentMain,QWidget *parent = nullptr);

private:
    MainWindow* mainWindow;
    QLineEdit *Author; //
    QTextEdit *questionBox; //
    PostManager &postManager; //
    QListWidget *viewQuestionBox;//
private slots: //
    void handleSubmit(); //
    void onShowPostsclicked();
    void handlePrevious();
};
#endif //USER_UI_STUDENTWINDOW_H