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
#include <QTimer>


class MainWindow; //

class StudentWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit StudentWindow(PostManager &pm,const QString &username, MainWindow* parentMain,QWidget *parent = nullptr);

private:
    MainWindow* mainWindow;
    QLineEdit *Author; //
    QTextEdit *questionBox; //
    QTextEdit *answerBox;
    PostManager &postManager; //
    QListWidget *viewQuestionBox;//
    QListWidget *relatedQuestions;
    QListWidget *answers;
    QString tempUsername;
    QTimer *refreshTimer;
    int selectedQuestion = -1;
    void refreshPosts();

private slots: //
    void handleSubmit(); //
    void onShowPostsclicked();
    void onQuestionClicked(int row);
    void handleAnsSubmit();
    void handlePrevious();
    void updateSuggestions();
};
#endif //USER_UI_STUDENTWINDOW_H