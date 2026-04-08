//
// Created by axelpc on 2/11/2026.
//

#ifndef USER_UI_REVIEWERWINDOW_H
#define USER_UI_REVIEWERWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "PostManager.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include "PostManager.h"
#include "MainWindow.h"

class MainWindow;

class ReviewerWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit ReviewerWindow(PostManager &pm, MainWindow* parentMain, QWidget *parent = nullptr);
private slots:
    //void onShowPostsClicked();

private:
    //QStackedWidget *stack;
    MainWindow* mainWindow;
    PostManager &postManager; //
    //QTextEdit *reviewBox; //
    QVBoxLayout *postsLayout;
    void displayPosts(const QString &filter);

private slots:
    void handlePrevious();
    void onFilterChanged(const QString &text);
};

#endif //USER_UI_REVIEWERWINDOW_H