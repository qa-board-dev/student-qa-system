//
// Created by axelpc on 2/11/2026.
//

#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include "ReviewerWindow.h"
#include "PostWidget.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QScrollArea>
#include "ReviewerWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QMessageBox>
#include <QTimer>

#include "ReviewerWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QMessageBox>
#include <QTimer>

ReviewerWindow::ReviewerWindow(PostManager &pm, const QString &username, MainWindow* parentMain, QWidget *parent)
    :QMainWindow(parent), postManager(pm), mainWindow(parentMain), tempUsername(username)
{
    resize(1200, 800);

    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setStyleSheet("background-color: #d3d3d3;");

    QWidget* container = new QWidget;
    QVBoxLayout* outerLayout = new QVBoxLayout(container);

    QWidget* card = new QWidget;
    card->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 15px;
        }
        QLabel{
            color: #000000;
        }
    )");

    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(15);
    cardLayout->setContentsMargins(20, 20, 20, 20);

    outerLayout->addWidget(card);
    mainLayout->addWidget(container);

    QWidget *header = new QWidget;
    header->setFixedHeight(70);
    header->setStyleSheet(R"(
        QWidget {
            background-color: #f5f7fa;
            border-radius: 10px;
            padding: 8px;
        }
    )");

    QHBoxLayout *headerLayout = new QHBoxLayout(header);

    QLabel *title = new QLabel("Reviewer Dashboard");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #000000;");

    QLabel *userLabel = new QLabel(tempUsername);
    userLabel->setStyleSheet(R"(
        QLabel{
            background-color:#e8f0fe;
            color:#1f618d;
            padding: 6px 12px;
            border-radius: 12px;
            font-weight: bold;
        }
    )");
    QString pillshape = "QPushButton {"
        " background-color: #0078d7;"
        " color: white;"
        " border-radius: 20px;"
        " padding: 8px 16px;"
        " font-size: 14px;"
        "}"
        "QPushButton:hover {"
        " background-color:#1f618d;"
        "}";
    QLabel *loggedText = new QLabel("Logged in as");
    loggedText->setStyleSheet("color: #555; font-size: 12px;");

    headerLayout->addWidget(title);
    headerLayout->addStretch();
    headerLayout->addWidget(loggedText);
    headerLayout->addWidget(userLabel);

    cardLayout->addWidget(header);

    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color: #ddd;");
    cardLayout->addWidget(line);

    viewQuestionBox = new QListWidget(this);
    answers = new QListWidget(this);

    feedbackBox = new QTextEdit(this);
    feedbackBox->setPlaceholderText("Write reviewer feedback...");

    QHBoxLayout *buttonlayout = new QHBoxLayout();
    buttonlayout->setSpacing(20);

    QPushButton *submitFeedbackBtn = new QPushButton("Submit Feedback");
    submitFeedbackBtn->setFixedWidth(150);
    submitFeedbackBtn->setFixedHeight(40);
    submitFeedbackBtn->setStyleSheet(pillshape);

    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setFixedWidth(150);
    logoutBtn->setFixedHeight(40);
    logoutBtn->setStyleSheet(pillshape);

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setFixedWidth(150);
    backBtn->setFixedHeight(40);
    backBtn->setStyleSheet(pillshape);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    QWidget *leftPane = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPane);

    leftLayout->addWidget(new QLabel("Questions"));
    leftLayout->addWidget(viewQuestionBox);

    QWidget *rightPane = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPane);

    rightLayout->addWidget(new QLabel("Answers"));
    rightLayout->addWidget(answers);
    rightLayout->addWidget(new QLabel("Feedback"));
    rightLayout->addWidget(feedbackBox);
    rightLayout->addWidget(submitFeedbackBtn);

    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1,1);

    cardLayout->addWidget(splitter);
    cardLayout->addLayout(buttonlayout);

    QHBoxLayout *bottom = new QHBoxLayout();
    bottom->addWidget(backBtn);
    bottom->addWidget(logoutBtn);

    cardLayout->addWidget(splitter);
    cardLayout->addLayout(bottom);

    QString inputStyle = R"(
        QLineEdit, QTextEdit, QListWidget{
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 10px;
            color: #000000;
            background-color: #ffffff;
            font-size: 16px;
        }
        QText:focus, QLineEdit:focus{
            border: 1px solid #3498db;
        }
        QLineEdit::placeholder {
            color: #888;
}
)";

    viewQuestionBox->setStyleSheet(inputStyle);
    answers->setStyleSheet(inputStyle);
    feedbackBox->setStyleSheet(inputStyle);

    setCentralWidget(widget);

    connect(viewQuestionBox, &QListWidget::currentRowChanged,this, &ReviewerWindow::onQuestionClicked);

    connect(submitFeedbackBtn, &QPushButton::clicked,this, &ReviewerWindow::handleFeedbackSubmit);

    connect(backBtn, &QPushButton::clicked,this, &ReviewerWindow::handleBack);

    connect(logoutBtn, &QPushButton::clicked, this, [this]() {
        if (mainWindow) {
            mainWindow->showLoginScreen();
        }
        this->close();
    });

    loadQuestions();

    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &ReviewerWindow::refreshPosts);
    refreshTimer->start(3000);
}

void ReviewerWindow::onShowPostsclicked() {
    const auto &posts = postManager.getPost();
    viewQuestionBox->clear();

    for (const Post &p : posts) {
        QString postText = p.getAuthor() + ": " + p.getContent();
        viewQuestionBox->addItem(postText);
    }
}
void ReviewerWindow::loadQuestions() {
    viewQuestionBox->clear();

    const auto &posts = postManager.getPost();

    for (const Post &p : posts) {
        QString postText = p.getAuthor()+": " + p.getContent();
        viewQuestionBox->addItem(postText);
    }
}

// ================= CLICK QUESTION =================
void ReviewerWindow::onQuestionClicked(int row) {
    selectedQuestion = row;
    answers->clear();

    if (selectedQuestion < 0) return;

    auto &posts = postManager.getPost();

    for (const Answer &a : posts[row].getAnswers()) {
        QString displayText;
        if (a.isReviewer) {
            displayText = "Reviewer " + a.author + ": " + a.content;
        }else {
            displayText = a.author + ": " + a.content;
        }

        answers->addItem(displayText);
    }
}

// ================= FEEDBACK =================
void ReviewerWindow::handleFeedbackSubmit() {
    if (selectedQuestion < 0) {
        QMessageBox::information(this, "Error", "Select a question first");
        return;
    }

    QString feedback = feedbackBox->toPlainText();
    QString author = tempUsername;

    if (feedback.isEmpty()) {
        QMessageBox::information(this, "Error", "Feedback cannot be empty");
        return;
    }

    Answer ans;
    ans.author = author;
    ans.content = feedback;
    ans.isReviewer = true;

    postManager.getPost()[selectedQuestion].addAnswer(ans);
    postManager.save();
    feedbackBox->clear();
    loadQuestions();
    onQuestionClicked(selectedQuestion);

}

// ================= BACK =================
void ReviewerWindow::handleBack() {
    if (mainWindow) {
        mainWindow->showRoleSelection();
    }
    this->hide();
}
void ReviewerWindow::refreshPosts() {
    int prevSelected = viewQuestionBox->currentRow();

    postManager.load();
    onShowPostsclicked();

    if (prevSelected >= 0 && prevSelected < viewQuestionBox->count()) {
        viewQuestionBox->setCurrentRow(prevSelected);
        onQuestionClicked(prevSelected);
    }
}