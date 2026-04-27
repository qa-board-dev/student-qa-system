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
#include <QTimer>
#include <QMap>


class MainWindow;

class ReviewerWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit ReviewerWindow(PostManager &pm, const QString &username, MainWindow* parentMain, bool showBack = false, QWidget *parent = nullptr);

private:
    PostManager &postManager;
    MainWindow* mainWindow;
    QString tempUsername;

    QListWidget *viewQuestionBox;
    QListWidget *answers;
    QTextEdit *feedbackBox;
    QMap<int, QString> feedbackMap;
    int selectedQuestion = -1;

    QTimer *refreshTimer;
    void displayPosts(const QString &filter);
    void refreshPosts();

private slots:
    void onShowPostsclicked();
    void loadQuestions();
    void onQuestionClicked(int row);
    void handleFeedbackSubmit();
    void handleBack();
};

#endif //USER_UI_REVIEWERWINDOW_H