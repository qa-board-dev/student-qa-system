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

ReviewerWindow::ReviewerWindow(PostManager &pm, const QString &username, MainWindow* parentMain, QWidget *parent)
    : QMainWindow(parent), postManager(pm), mainWindow(parentMain), tempUsername(username){
    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setStyleSheet("background-color: #d3d3d3;");

    QWidget *container = new QWidget;
    QVBoxLayout *outerLayout = new QVBoxLayout(container);

    QWidget *card = new QWidget;
    card->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 15px;
        }
    )");

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(20, 20, 20, 20);
    cardLayout->setSpacing(15);

    outerLayout->addWidget(card);
    mainLayout->addWidget(container);

    QWidget *header = new QWidget;
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

    QLabel *loggedText = new QLabel("Logged in as");
    loggedText->setStyleSheet("color: #555; font-size: 12px;");

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

    headerLayout->addWidget(title);
    headerLayout->addStretch();

    headerLayout->addWidget(loggedText);
    headerLayout->addWidget(userLabel);

    cardLayout->addWidget(header);

    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color: #ddd;");
    cardLayout->addWidget(line);

    QComboBox *filterBox = new QComboBox;
    filterBox->setStyleSheet(R"(
        QComboBox {
        background-color: #ffffff;
        border: 1px solid #dcdcdc;
        border-radius: 8px;
        padding: 6px 12px;
        padding-right: 25px;
        font-size: 13px;
        color: #222;
        }
        QComboBox:hover {
      border: 1px solid #999
      }

       QComboBox::drop-down {
        sub-control-origin: padding
        sub-control-position: top right;
        width: 20px;
        border: none;
        width: 20px;
       }
      QComboBox::down-arrow {
      image: none;
      border-left: 5px solid transparency;
      border-right: 6px solid #555;
      border-top: 6px solid #555;
      margin-right: 8px;
}

       QComboBox QAbstractItemView {
        background-color: #ffffff;
        border: 1px solid #ddd;
        border-radius: 6px;
        selection-background-color: #f0f2f5;

       }
         )");

    filterBox->setEditable(true);
    filterBox->lineEdit()->setReadOnly(true);
    filterBox->addItems({"All Posts","UpVoted","DownVoted"});
    filterBox->setCurrentIndex(-1);
    filterBox->lineEdit()->setPlaceholderText("Options");

    cardLayout->addWidget(filterBox);

    postsLayout = new QVBoxLayout();

    QWidget *postsContainer = new QWidget;
    postsContainer->setLayout(postsLayout);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(postsContainer);
    scrollArea->setStyleSheet("border: none;");

    cardLayout->addWidget(scrollArea);

    QHBoxLayout *bottomLayout = new QHBoxLayout();

    QPushButton *previousBtn = new QPushButton("Previous");

    QString pill = R"(
        QPushButton {
            background-color: #3498db;
            color: white;
            border-radius: 20px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color:#1f618d;
        }
    )";

    previousBtn->setStyleSheet(pill);
    previousBtn->setFixedSize(150, 40);

    bottomLayout->addStretch();
    bottomLayout->addWidget(previousBtn);
    bottomLayout->addStretch();

    cardLayout->addLayout(bottomLayout);

    setCentralWidget(widget);

    connect(filterBox, &QComboBox::currentTextChanged,
            this, &ReviewerWindow::onFilterChanged);

    connect(previousBtn, &QPushButton::clicked,
            this, &ReviewerWindow::handlePrevious);

    displayPosts("All Posts");
}
void ReviewerWindow::onFilterChanged(const QString &text){
    displayPosts(text);
}
void ReviewerWindow::displayPosts(const QString &filter) {
    QLayoutItem *item;
    while ((item = postsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
   //qDebug() << "Post count: " << postManager.getPost().size();
    for (const Post &p : postManager.getPost()) {
        if (filter == "All Posts") {
            PostWidget *widget = new PostWidget(p.getAuthor(),p.getContent(),p.getAnswers());
            postsLayout->addWidget(widget);
        }
    }
}
void ReviewerWindow::handlePrevious() {
    if (mainWindow) {
        mainWindow->showRoleSelection();
    }
    this->hide();
}
/*
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Reviewer Dashboard");
    title->setAlignment(Qt::AlignCenter);

    QListWidget *answersToReview = new QListWidget;

    reviewBox = new QTextEdit(this);//
    reviewBox->setPlaceholderText("Write your review here: ");

    QPushButton *submitReview = new QPushButton("Submit Review");
    QPushButton *logoutBtn = new QPushButton("Logout");
    QPushButton *ShowPosts = new QPushButton("Show Posts"); //


    layout->addWidget(title);
    layout->addWidget(new QLabel("Answers:"));
    layout->addWidget(answersToReview);
    layout->addWidget(new QLabel("Review:"));
    layout->addWidget(reviewBox);
    layout->addWidget(submitReview);
    layout->addWidget(ShowPosts);
    layout->addWidget(logoutBtn);

    setCentralWidget(widget);

    connect(ShowPosts, &QPushButton::clicked, this, &ReviewerWindow::onShowPostsClicked);
    connect(logoutBtn, &QPushButton::clicked, this, &QWidget::close);

}
void ReviewerWindow::onShowPostsClicked() {
    //qDebug() << "ShowPosts clicked!";
    //if (!reviewBox) {
       // qDebug()<< "reviewBox is null!";
        //return;
    //}
    // reviewBox->clear();

    const auto &posts = postManager.getPost();
    if (posts.size()==0) {
        QMessageBox::information(this,"Error","No posts available");
    }
    reviewBox->clear();
    for (const Post &p : posts) {
        QString postText;
        postText += "Author: " + p.getAuthor() + "\n"; //QString change
        postText += "Content: " + p.getContent() + "\n"; //QString change
      reviewBox->append(postText);
    }
}
*/
