//
// Created by axelpc on 2/11/2026.
//
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include "StudentWindow.h"
#include <QLineEdit>
#include "MainWindow.h"
using namespace std;
#include <string>
#include "Post.h"
#include <QMessagebox.h>
#include <QSplitter>
#include <QFrame>

StudentWindow::StudentWindow(PostManager &pm, const QString &username, MainWindow* parentMain, bool showBack, QWidget *parent)
    :QMainWindow(parent), postManager(pm), mainWindow(parentMain), tempUsername(username) {
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
        QLabel {
            color: #000000;
            font-size: 16px;
        }
        QLineEdit::placeholder {
            color #888;
            font-size: 25px;
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

    QLabel *title = new QLabel("Student Dashboard");
    title->setStyleSheet("font-size: 25px; font-weight: bold; color: #000000;");

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

    questionBox = new QTextEdit(this);
    questionBox->setPlaceholderText("Ask your question here: ");
    viewQuestionBox = new QListWidget(this);
    relatedQuestions = new QListWidget(this);

    QHBoxLayout *buttonlayout = new QHBoxLayout();
    buttonlayout->setSpacing(20);

    answers = new QListWidget(this);
    answerBox = new QTextEdit(this);
    answerBox->setPlaceholderText("Type your answer here: ");

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

    QPushButton *submitAns = new QPushButton("Submit Answer");
    submitAns->setFixedWidth(150);
    submitAns->setFixedHeight(40);
    submitAns->setStyleSheet(pillshape);

    QPushButton *submitBtn = new QPushButton("Submit Question");
    submitBtn->setFixedWidth(150);
    submitBtn->setFixedHeight(40);
    submitBtn->setStyleSheet(pillshape);

    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setFixedWidth(150);
    logoutBtn->setFixedHeight(40);
    logoutBtn->setStyleSheet(pillshape);

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setFixedWidth(150);
    backBtn->setFixedHeight(40);
    backBtn->setStyleSheet(pillshape);
    backBtn->setVisible(showBack);

    buttonlayout->addStretch();
    buttonlayout->addWidget(backBtn);
    buttonlayout->addWidget(logoutBtn);
    buttonlayout->addStretch();

    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    QWidget *leftPane = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPane);

    leftLayout->addWidget(new QLabel("Related Questions:"));
    leftLayout->addWidget(relatedQuestions);
    leftLayout->addWidget(new QLabel("Questions List:"));
    leftLayout->addWidget(viewQuestionBox);
    leftLayout->addWidget(new QLabel("Your Question:"));
    leftLayout->addWidget(questionBox);
    leftLayout->addWidget(submitBtn);

    QWidget *rightPane = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPane);

    rightLayout->addWidget(new QLabel("Answers:"));
    rightLayout->addWidget(answers);
    rightLayout->addWidget(answerBox);

    QHBoxLayout *answerBtnLayout = new QHBoxLayout();
    answerBtnLayout->addStretch();
    answerBtnLayout->addWidget(submitAns);

    rightLayout->addLayout(answerBtnLayout);

    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 1);

    cardLayout->addWidget(splitter);
    cardLayout->addLayout(buttonlayout);

    QString inputStyle = R"(
        QLineEdit, QTextEdit, QListWidget{
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 10px;
            color: #000000;
            background-color: #ffffff;
            font-size: 16px;
        }
        QTextEdit:focus, QLineEdit:focus {
            border: 1px solid #3498db;
        }
        QLineEdit::placeholder {
            color: #888;
        }
    )";


    answerBox->setStyleSheet(inputStyle);
    viewQuestionBox->setStyleSheet(inputStyle);
    questionBox->setStyleSheet(inputStyle);
    relatedQuestions->setStyleSheet(inputStyle);
    answers->setStyleSheet(inputStyle);

    setCentralWidget(widget);

    connect(questionBox, &QTextEdit::textChanged, this, &StudentWindow::updateSuggestions);
    connect(backBtn, &QPushButton::clicked, this, &StudentWindow::handlePrevious);
    connect(submitBtn, &QPushButton::clicked,this, &StudentWindow::handleSubmit);

    connect(logoutBtn, &QPushButton::clicked, this, [this]() {
        if (mainWindow) {
            mainWindow->showLoginScreen();
        }
        this->close();
    });


    connect(viewQuestionBox, &QListWidget::currentRowChanged, this, &StudentWindow::onQuestionClicked);
    connect(submitAns, &QPushButton::clicked, this, &StudentWindow::handleAnsSubmit);

    connect(relatedQuestions, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        QString text = item->text();
        auto &posts = postManager.getPost();
        for (int i = 0; i < posts.size(); ++i) {
            if ((posts[i].getAuthor() + ":" + posts[i].getContent() == text)) {
                viewQuestionBox->setCurrentRow(i);
                onQuestionClicked(i);
                break;
            }
        }
    });

    onShowPostsclicked();

    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &StudentWindow::refreshPosts);
    refreshTimer->start(3000);
}
void StudentWindow::handleSubmit(){
    QString author = tempUsername;
    QString content = questionBox->toPlainText();

    try {
        Post newPost(tempUsername, content);
        postManager.addPost(newPost);
        postManager.save();
        //qDebug << "Added post. Total Posts:
        questionBox->clear();
        QMessageBox::information(this, "Success", "Post Submitted!");
    }
    catch (invalid_argument&) {
        QMessageBox::information(this, "Error","One or more boxes is empty ");
    }

    onShowPostsclicked();
}

void StudentWindow::onShowPostsclicked() {
    const auto &posts = postManager.getPost();
    viewQuestionBox->clear();

    for (const Post &p : posts) {
        QString postText = p.getAuthor()+": " + p.getContent(); //QString change
        viewQuestionBox->addItem(postText);
    }
}

void StudentWindow::handlePrevious() {
    if (mainWindow) {
        mainWindow->showRoleSelection();
    }
    this->hide();
}
void StudentWindow::updateSuggestions() {
    QString content = questionBox->toPlainText();

    if (content.trimmed().isEmpty()) {
        relatedQuestions->clear();
        return;
    }
    Post temp("temp_User", content);
    auto suggestions = postManager.getRelated(temp);
    relatedQuestions->clear();
    for (const Post &p : suggestions) {
        relatedQuestions->addItem(p.getAuthor() + ":" + p.getContent());
    }
}

void StudentWindow::onQuestionClicked(int row) {
    selectedQuestion = row;
    answers->clear();

    if (selectedQuestion < 0) {
        return;
    }

    auto &posts = postManager.getPost();

    for (const Answer& a : posts[row].getAnswers()) {
        QString displayText;
        if (a.isReviewer) {
            displayText = "Reviewer " + a.author + ": " + a.content;
        } else {
            displayText = a.author + ": " + a.content;
        }

        QListWidgetItem *item = new QListWidgetItem(displayText);
        if (a.isReviewer) {
            item->setForeground(QColor("#1f618d"));
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);
        }
        answers->addItem(item);
    }
}

void StudentWindow::handleAnsSubmit() {
    if (selectedQuestion < 0) {
        QMessageBox::information(this,"Error","Select a question first");
        return;
    }

    QString answerText = answerBox->toPlainText();
    QString author = tempUsername;

    if (answerText.isEmpty()) {
        QMessageBox::information(this,"Error","Username or Answer missing");
        return;
    }

    Answer ans;
    ans.author = author;
    ans.content = answerText;

    postManager.getPost()[selectedQuestion].addAnswer(ans);
    postManager.save();
    answerBox->clear();
    onQuestionClicked(selectedQuestion);
    onShowPostsclicked();
}

void StudentWindow::refreshPosts() {
    int prevSelected = viewQuestionBox->currentRow();

    postManager.load();
    onShowPostsclicked();

    if (prevSelected >= 0 && prevSelected < viewQuestionBox->count()) {
        viewQuestionBox->setCurrentRow(prevSelected);
        onQuestionClicked(prevSelected);
    }
}