//
// Created by axel_ on 2/11/2026.
//

#include "MainWindow.h"
#include <QtWidgets>
#include <QSettings>
#include <QVBoxLayout>
#include <qMessageBox>
#include "AdminWindow.h"
#include "StudentWindow.h"
#include "ReviewerWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model.load();

    stack = new QStackedWidget(this);
    setCentralWidget(stack);
    setMinimumSize(900,600);

    stack->addWidget(createLoginScreen());          //0
    stack->addWidget(createFirstUserSetupScreen()); //1
    stack->addWidget(createRoleSelectionScreen());  //2
    stack->addWidget(createSignupScreen());         //3

    stack->setCurrentIndex(0);

}

void MainWindow::switchScreen(QWidget *screen)
{
    stack->setCurrentWidget(screen);
}

QWidget* MainWindow::createLoginScreen()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setStyleSheet("background-color: #d3d3d3");

    QWidget* container = new QWidget;
    QVBoxLayout* outerLayout = new QVBoxLayout(container);
    outerLayout->setAlignment(Qt::AlignCenter);

    QWidget* card = new QWidget;
    card->setFixedWidth(300);
    card->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 10px;
        }
        )");

    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(15);
    cardLayout->setContentsMargins(30, 30, 30, 30);
    cardLayout->addSpacing(10);

    outerLayout->addWidget(card);
    mainLayout->addWidget(container);

    QLabel *title = new QLabel("Student Q&A System\n Login");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #000000;");

    QLineEdit *username = new QLineEdit;
    username->setPlaceholderText("Username");

    QLineEdit *password = new QLineEdit;
    password->setPlaceholderText("Password");
    password->setEchoMode(QLineEdit::Password);

    QPushButton *loginBtn = new QPushButton("Login");
    loginBtn->setStyleSheet("background-color: #0078d7; color: white; padding: 10px; border-radius: 6px;");

    QPushButton *firstUserBtn = new QPushButton("First User Setup");

    QPushButton *signupBtn = new QPushButton("Sign Up");
    signupBtn->setStyleSheet(R"(
        QPushButton {
            background: transparent;
            color: #0078d7;
            border: none;
        }
        QPushButton:hover {
            text-decoration: underline;
        }
    )");

    cardLayout->addWidget(title);
    cardLayout->addWidget(username);
    cardLayout->addWidget(password);
    cardLayout->addWidget(loginBtn);
    cardLayout->addWidget(firstUserBtn);
    cardLayout->addWidget(signupBtn);

    QString inputStyle = R"(
        QLineEdit {
            padding: 8px;
            border: 1px solid #ccc;
            border-radius: 6px;
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

    username->setStyleSheet(inputStyle);
    password->setStyleSheet(inputStyle);

    connect(loginBtn, &QPushButton::clicked, this, [this, username, password](){
        if (model.authenticate(username->text(), password->text())) {
            stack->setCurrentIndex(2);
        } else {
            QMessageBox::warning(this, "Error", "Login failed!");
        }
    });

    connect(firstUserBtn, &QPushButton::clicked, this, [this]() {
        stack->setCurrentIndex(1);
    });

    connect(signupBtn, &QPushButton::clicked, this, [this]()
    {
      stack->setCurrentIndex(3);
    });

    if (!model.firstUser()) {
        firstUserBtn->hide();
    }

    if (model.firstUser())
    {
        signupBtn->hide();
    }

    return widget;
}

QWidget* MainWindow::createFirstUserSetupScreen()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setStyleSheet("background-color: #d3d3d3;");

    QWidget* container = new QWidget;
    QVBoxLayout* outerLayout = new QVBoxLayout(container);
    outerLayout->setAlignment(Qt::AlignCenter);

    QWidget* card = new QWidget;
    card->setFixedWidth(300);
    card->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 10px;
        }
        )");

    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(15);
    cardLayout->setContentsMargins(30, 30, 30, 30);
    cardLayout->addSpacing(10);

    outerLayout->addWidget(card);
    mainLayout->addWidget(container);

    QLabel *title = new QLabel("First User Setup (Admin)");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #000000;");

    QLineEdit *username = new QLineEdit;
    username->setPlaceholderText("Admin Username");

    QLineEdit *password = new QLineEdit;
    password->setPlaceholderText("Password");
    password->setEchoMode(QLineEdit::Password);

    QPushButton *createBtn = new QPushButton("Create Admin Account");
    createBtn->setStyleSheet("background-color: #0078d7; color: white; padding: 10px; border-radius: 6px;");

    cardLayout->addWidget(title);
    cardLayout->addWidget(username);
    cardLayout->addWidget(password);
    cardLayout->addWidget(createBtn);

    QString inputStyle = R"(
        QLineEdit {
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

    username->setStyleSheet(inputStyle);
    password->setStyleSheet(inputStyle);

    connect(createBtn, &QPushButton::clicked, this, [this, username, password](){
        model.addUser(username->text(), password->text(), {"admin"});
        model.save();
		QSettings settings("Admin", "QA");
		settings.setValue("AdminCreated", true);
        QMessageBox::information(this, "Success",
                                 "Admin created. Please login again.");
        stack->setCurrentIndex(0);
    });

    return widget;
}

QWidget* MainWindow::createSignupScreen()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setStyleSheet("background-color: #d3d3d3");

    QWidget* container = new QWidget;
    QVBoxLayout* outerLayout = new QVBoxLayout(container);
    outerLayout->setAlignment(Qt::AlignCenter);

    QWidget* card = new QWidget;
    card->setFixedWidth(300);
    card->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 10px;
        }
        )");


    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(15);
    cardLayout->setContentsMargins(30, 30, 30, 30);
    cardLayout->addSpacing(10);
    //cardLayout->setGraphicsEffect(new QGraphicsDropShadowEffect());

    outerLayout->addWidget(card);
    mainLayout->addWidget(container);

    QLabel *title = new QLabel("Sign Up");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #000000;");

    QLineEdit *username = new QLineEdit;
    username->setPlaceholderText("Username");

    QLineEdit *password = new QLineEdit;
    password->setPlaceholderText("Password");
    password->setEchoMode(QLineEdit::Password);

    QLineEdit *inviteCode = new QLineEdit;
    inviteCode->setPlaceholderText("Invite Code");
    //inviteCode->setEchoMode(QLineEdit::inviteCode);

    QPushButton *nextBtn = new QPushButton("Next");

    QPushButton* backButton = new QPushButton("Back to login");
    backButton->setStyleSheet(R"(
        QPushButton{
            background: transparent;
            color: #0078d7;
            border: none;
        }
        QPushButton:hover{
            text-decoration: underline;
        }
)");

    cardLayout->addWidget(title);
    cardLayout->addWidget(username);
    cardLayout->addWidget(password);
    cardLayout->addWidget(inviteCode);
    cardLayout->addWidget(nextBtn);
    cardLayout->addWidget(backButton);

    QString inputStyle = R"(
        QLineEdit {
            padding: 8px;
            border: 1px solid #ccc;
            border-radius: 6px;
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
    username->setStyleSheet(inputStyle);
    password->setStyleSheet(inputStyle);
    inviteCode->setStyleSheet(inputStyle);

    nextBtn->setStyleSheet("background-color:#0078d7; color:white; padding:10px; border-radius:6px;");

    connect(nextBtn, &QPushButton::clicked, this,
        [this, username, password, inviteCode]() {

        if (username->text().isEmpty() || password->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Fill all fields");
            return;
        }

        if (!isValidInviteCode(inviteCode->text())) {
            QMessageBox::warning(this, "Error", "Invalid invite code");
            return;
        }

        tempUsername = username->text();
        tempPassword = password->text();
        tempInviteCode = inviteCode->text();

        signupMode = true;
        stack->setCurrentIndex(2); // go to role selection
    });
    if (signupMode)
    {
        title->setText("Choose Role for New Account");
    }
    connect(backButton, &QPushButton::clicked, this, [this]()
            {
                stack->setCurrentIndex(0);
            });

    return widget;
}

QWidget* MainWindow::createRoleSelectionScreen()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setStyleSheet("background-color: #d3d3d3;");

    QWidget* container = new QWidget;
    QVBoxLayout *outerLayout = new QVBoxLayout(container);
    outerLayout->setAlignment(Qt::AlignCenter);

    QWidget* card = new QWidget;
    QVBoxLayout  *cardLayout = new QVBoxLayout(card);
    card->setFixedWidth(300);
    card->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 10px;
        }
        )");
    cardLayout->setSpacing(15);
    cardLayout->setContentsMargins(30, 30, 30, 30);
    cardLayout->addSpacing(10);
    cardLayout->setSpacing(20);

    outerLayout->addWidget(card);
    mainLayout->addWidget(container);

    QLabel *title = new QLabel("Select Role");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #000000;");

    QPushButton *adminBtn = new QPushButton("Admin");
    adminBtn->setStyleSheet("background-color: #0078d7; color:white; padding:10px; border-radius:6px;");
    QPushButton *studentBtn = new QPushButton("Student");
    studentBtn->setStyleSheet("background-color: #0078d7; color:white; padding:10px; border-radius:6px;");
    QPushButton *reviewerBtn = new QPushButton("Reviewer");
    reviewerBtn->setStyleSheet("background-color: #0078d7; color:white; padding:10px; border-radius:6px;");
    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setStyleSheet(R"(
        QPushButton {
            background: transparent;
            color: #0078d7;
            border: none;
        }
        QPushButton:hover {
            text-decoration: underline;
        }
        )");

    cardLayout->addWidget(title);
    cardLayout->addWidget(adminBtn);
    cardLayout->addWidget(studentBtn);
    cardLayout->addWidget(reviewerBtn);
    cardLayout->addWidget(logoutBtn);

    QString inputStyle = R"(
        QLineEdit {
        padding: 8px;
        border: 1px solid #ccc;
        border-radius: 6px;
        color: #00000;
            background-color: #fafafa;
        }
        QLineEdit:focus {
            border: 1px solid #0078d7;
        }
        )";

    connect(adminBtn, &QPushButton::clicked, this, [this]() {
        AdminWindow *admin = new AdminWindow(this);

        connect(admin, &AdminWindow::logoutRequest, this, [this, admin]() {
            this->show();
            admin->close();
            admin->deleteLater();
            stack->setCurrentIndex(0);
        });

        admin->show();
		this->hide();
    });

    connect(studentBtn, &QPushButton::clicked, this, [this]() {

        if (signupMode)
        {
            if (!model.addUser(tempUsername, tempPassword, {"student"}))
            {
                QMessageBox::warning(this, "Error", "Username exists");
                return;
            }
            model.save();
            signupMode = false;

            QMessageBox::information(this, "Success", "Account created!");
            stack->setCurrentIndex(0);
            return;
        }
        postManager.load();
        StudentWindow *student = new StudentWindow(postManager,this); //
        student->show();
        this->hide();
    });

    connect(reviewerBtn, &QPushButton::clicked, this, [this]() {

        if (signupMode)
        {
            if (!model.addUser(tempUsername, tempPassword, {"reviewer"}))
            {
                QMessageBox::warning(this, "Error", "Username exists");
                return;
            }
            model.save();
            signupMode = false;

            QMessageBox::information(this, "Success", "Account created!");
            stack->setCurrentIndex(0);
            return;
        }

        ReviewerWindow *reviewer = new ReviewerWindow(postManager, this);
        reviewer->show();
        this->hide();
	});

 connect(logoutBtn, &QPushButton::clicked, this, [this]() {
    stack->setCurrentIndex(0);
	});

    return widget;
}

bool MainWindow::isValidInviteCode(const QString& code)
{
    QFile file("codes.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&file);

    while (!in.atEnd())
    {
        if (in.readLine().trimmed() == code){
        return true;
        }
    }
    return false;
}

void MainWindow::showRoleSelection() {
    stack->setCurrentIndex(2);
    this->show();
}