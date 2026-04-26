//
// Created by axelpc on 2/11/2026.
//
#include "AdminWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QMessageBox>

AdminWindow::AdminWindow(CodeManager& cm, QWidget *parent) : QMainWindow(parent), codeManager(cm)
{
    resize(900, 600);
    setWindowTitle("Admin Dashboard");

    QWidget *widget = new QWidget;
    QVBoxLayout *mainlayout = new QVBoxLayout(widget);
    mainlayout->setContentsMargins(30, 30, 30, 30);
    mainlayout->setAlignment(Qt::AlignCenter);

    widget->setStyleSheet("background-color: #d3d3d3;");

    QWidget *container = new QWidget;
    QVBoxLayout *outerLayout = new QVBoxLayout(container);
    outerLayout->setAlignment(Qt::AlignCenter);

    QWidget *card = new QWidget;
    card->setFixedWidth(500);
    card->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 18px;
        }

        QLabel {
            background-color:#e8f0fe;
            color:#1f618d;
            padding: 6px 12px;
            border-radius: 12px;
            font-weight: bold;
        }

        QLineEdit, QDateEdit {
            padding: 10px;
            border: 1px solid #dcdcdc;
            border-radius: 10px;
            background-color: white;
            color: black;
            font-size: 14px;
        }

        QLineEdit:focus, QDateEdit:focus {
            border: 1px solid #3498db;
        }

        QLineEdit::placeholder {
            color: #888;
        }
    )");

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(18);
    cardLayout->setContentsMargins(30,30,30,30);

    outerLayout->addWidget(card);
    mainlayout->addWidget(container);

    QWidget *header = new QWidget;
    header->setFixedHeight(70);
    header->setStyleSheet(R"(
        QWidget {
            background-color: #f5f7fa;
            border-radius: 12px;
            padding: 8px;
        }
    )");

    QHBoxLayout *headerLayout = new QHBoxLayout(header);

    QLabel *title = new QLabel("Admin Dashboard");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size: 25px;"
        "font-weight: bold;"
        "color: #000000;"
        "background: transparent;"
        "padding: 0px;"
    );

    headerLayout->addStretch();
    headerLayout->addWidget(title);
    headerLayout->addStretch();

    QLineEdit *inviteCode = new QLineEdit;
    inviteCode->setPlaceholderText("One-time Invitation Code");
    inviteCode->setReadOnly(true);

    QDateEdit *deadline = new QDateEdit;
    deadline->setCalendarPopup(true);
    deadline->setDate(QDate::currentDate().addDays(7));
    deadline->setDisplayFormat("MM/dd/yyyy");
    deadline->setStyleSheet(R"(
    QDateEdit {
        padding: 10px;
        padding-right: 35px;
        border: 1px solid #dcdcdc;
        border-radius: 10px;
        background-color: white;
        color: black;
        font-size: 14px;
    }

    QDateEdit::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: top right;
        width: 28px;
        border-left: 1px solid #dcdcdc;
        background-color: #f5f7fa;
        border-top-right-radius: 10px;
        border-bottom-right-radius: 10px;
    }

    QDateEdit::drop-down:hover {
        background-color: #e8f0fe;
    }

    QDateEdit::down-arrow {
    width: 12px;
    height: 12px;
}
    QCalendarWidget QWidget {
        background-color: white;
        color: black;
    }

    QCalendarWidget QToolButton {
        color: black;
        font-weight: bold;
        background: transparent;
    }

    QCalendarWidget QMenu,
    QCalendarWidget QSpinBox {
        background: white;
        color: black;
    }

    QCalendarWidget QAbstractItemView {
        background-color: white;
        color: black;
        selection-background-color: #0078d7;
        selection-color: white;
        gridline-color: #dcdcdc;
    }
)");

    QString pillshape =
        "QPushButton {"
        " background-color: #0078d7;"
        " color: white;"
        " border: none;"
        " border-radius: 20px;"
        " padding: 8px 16px;"
        " font-size: 14px;"
        " font-weight: bold;"
        "}"
        "QPushButton:hover {"
        " background-color:#1f618d;"
        "}"
        "QPushButton:pressed {"
        " background-color:#154360;"
        "}";

    QPushButton *generateBtn = new QPushButton("Generate Invitation");
    generateBtn->setFixedWidth(200);
    generateBtn->setFixedHeight(42);
    generateBtn->setCursor(Qt::PointingHandCursor);
    generateBtn->setStyleSheet(pillshape);

    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setFixedWidth(200);
    logoutBtn->setFixedHeight(42);
    logoutBtn->setCursor(Qt::PointingHandCursor);
    logoutBtn->setStyleSheet(pillshape);

    cardLayout->addWidget(header);
    cardLayout->addSpacing(10);
    cardLayout->addWidget(inviteCode);
    cardLayout->addWidget(deadline);
    cardLayout->addSpacing(5);
    cardLayout->addWidget(generateBtn, 0, Qt::AlignCenter);
    cardLayout->addWidget(logoutBtn, 0, Qt::AlignCenter);

    setCentralWidget(widget);

    //connect(logoutBtn, &QPushButton::clicked, this, [this] {stack->setCurrentIndex(0);});

    connect(generateBtn, &QPushButton::clicked, this, [this, deadline, inviteCode]() {
        QString newInviteCode;

        if (deadline->date() < QDate::currentDate()) {
            QMessageBox::warning(this,
                                 "Selected Expiration Date Has Passed",
                                 "Please choose a future date.");
        } else {
            newInviteCode = codeManager.generate(deadline->date());
        }

        inviteCode->clear();
        inviteCode->setText(newInviteCode);
    });

    connect(logoutBtn, &QPushButton::clicked, this, [this]() {
        emit logoutRequest();
    });
}