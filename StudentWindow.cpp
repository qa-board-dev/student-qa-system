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



StudentWindow::StudentWindow(PostManager &pm, MainWindow* parentMain, QWidget *parent)
    :QMainWindow(parent), postManager(pm), mainWindow(parentMain) {
    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setStyleSheet("background-color: #d3d3d3;");

    QWidget* container = new QWidget;
    QVBoxLayout* outerLayout = new QVBoxLayout(container);

    QWidget* card = new QWidget;
    //card->setFixedWidth(850);
    card->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 15px;
        }
        QLabel {
            color: #000000;
        }
        )");

    QVBoxLayout* cardLayout = new QVBoxLayout(card);

    outerLayout->addWidget(card);
    mainLayout->addWidget(container);

    QLabel *title = new QLabel("Student Dashboard");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #000000;");

    Author = new QLineEdit(this);
    Author->setPlaceholderText(("Enter Name Here For Answers and Questions")); //

    questionBox = new QTextEdit(this);//
    questionBox->setPlaceholderText(("Ask your question here: "));
    viewQuestionBox = new QListWidget(this);//
    relatedQuestions = new QListWidget(this);

    //QListWidget *answersList = new QListWidget;
    QHBoxLayout *buttonlayout = new QHBoxLayout();

    StudentWindow::answers = new QListWidget(this);
    StudentWindow::answerBox = new QTextEdit(this);
    answerBox->setPlaceholderText("Type your answer here: ");
    QPushButton *submitAns = new QPushButton("Submit Answer");

    QString pillshape = "QPushButton {"
    " background-color: #3498db;"
    " color: white;"
    " border-radius: 20px;"
    " padding: 8px 16px;"
    " font-size: 14px;"
    "}"
    "QPushButton:hover {"
    " background-color:#1f618d;"
    "}";


    QPushButton *submitBtn = new QPushButton("Submit Question");
    submitBtn->setFixedWidth((150));
    submitBtn->setFixedHeight((40));
    submitBtn->setStyleSheet(pillshape);

    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setFixedWidth((150));
    logoutBtn->setFixedHeight((40));
    logoutBtn->setStyleSheet(pillshape);

    QPushButton *ShowPosts = new QPushButton("Show Posts"); //
    ShowPosts->setFixedWidth((150));
    ShowPosts->setFixedHeight((40));
    ShowPosts->setStyleSheet(pillshape);

    QPushButton *Previous = new QPushButton("Previous"); //
    Previous->setFixedWidth((150));
    Previous->setFixedHeight((40));
    Previous->setStyleSheet(pillshape);

    buttonlayout->addWidget(submitBtn);
    buttonlayout->addSpacing(20);
    //buttonlayout->addWidget(ShowPosts);
    //buttonlayout->addSpacing(20);
    buttonlayout->addWidget(Previous);
    buttonlayout->addSpacing(20);
    buttonlayout->addWidget(logoutBtn);

    cardLayout->addWidget(title);
    QLabel *AuthorTitle = new QLabel("Author");
    cardLayout->addWidget(AuthorTitle);
    cardLayout->addWidget(Author); //
    cardLayout->addWidget(new QLabel("Your Question:"));
    cardLayout->addWidget(questionBox);
    cardLayout->addWidget(new QLabel("Related Questions:"));
    cardLayout->addWidget(relatedQuestions);
    cardLayout->addWidget(new QLabel("Questions List:"));
    cardLayout->addWidget(viewQuestionBox);

    cardLayout->addWidget(new QLabel("Answers:"));
    cardLayout->addWidget(answers);
    cardLayout->addWidget(answerBox);
    cardLayout->addWidget(submitAns);

    //layout->addWidget(new QLabel("Question Answers:"));
    //layout->addWidget(answersList);
    cardLayout->addLayout(buttonlayout);//

    QString inputStyle = R"(
        QLineEdit, QTextEdit, QListWidget{
            padding: 8px;
            border: 1px solid #ccc;
            color: #000000;
            background-color: #fafafa;
        }
        QLineEdit:focus {
            border: 1px solid #0078d7;
        }
        QLineEdit::placeholder {
            color: #888;
        }
    )";

    Author->setStyleSheet(inputStyle);
    setCentralWidget(widget);
    questionBox->setStyleSheet(inputStyle);
    setCentralWidget(widget);
    answerBox->setStyleSheet(inputStyle);
    setCentralWidget(widget);
    viewQuestionBox->setStyleSheet(inputStyle);
    setCentralWidget(widget);
    relatedQuestions->setStyleSheet(inputStyle);
    setCentralWidget(widget);
    answers->setStyleSheet(inputStyle);
    setCentralWidget(widget);

    connect(questionBox, &QTextEdit::textChanged, this, &StudentWindow::updateSuggestions);
    connect(ShowPosts, &QPushButton::clicked, this, &StudentWindow::onShowPostsclicked);
    connect(Previous, &QPushButton::clicked, this, &StudentWindow::handlePrevious);
    connect(submitBtn, &QPushButton::clicked,this, &StudentWindow::handleSubmit); //
    connect(logoutBtn, &QPushButton::clicked, this, &QWidget::close);
    connect(viewQuestionBox, &QListWidget::currentRowChanged, this, &StudentWindow::onQuestionClicked);
    connect(submitAns, &QPushButton::clicked, this, &StudentWindow::handleAnsSubmit);

    //Connecting the show related questions to also show those answers when clicked
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

}
void StudentWindow::handleSubmit(){ //
    QString author = Author->text();//QString Change
    QString content = questionBox->toPlainText();
    try {
        Post newPost(author, content);
        postManager.addPost(newPost);
        postManager.save();
        //qDebug << "Added post. Total Posts:
        Author->clear();
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
        answers->addItem(a.author + ": " + a.content);
    }
}

void StudentWindow::handleAnsSubmit() {
    if (selectedQuestion < 0) {
        QMessageBox::information(this,"Error","Select a question first");
        return;
    }

    QString answerText = answerBox->toPlainText();
    QString author = Author->text();

    if (answerText.isEmpty() || author.isEmpty()) {
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