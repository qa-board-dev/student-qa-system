//
// Created by axelpc on 2/11/2026.
//

#ifndef USER_UI_REVIEWERWINDOW_H
#define USER_UI_REVIEWERWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "PostManager.h"
#include <QTextEdit>

class ReviewerWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit ReviewerWindow(PostManager &pm, QWidget *parent = nullptr);
private slots:
    void onShowPostsClicked();

private:
    QStackedWidget *stack;
    PostManager &postManager; //
    QTextEdit *reviewBox; //
};

#endif //USER_UI_REVIEWERWINDOW_H