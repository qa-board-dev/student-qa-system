//
// Created by axelpc on 2/11/2026.
//
#include "AdminWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>
#include <QMainWindow>
#include <QMessageBox>
#include <qrandom.h>
#include <QRandomGenerator>


AdminWindow::AdminWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(900, 600);

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("Admin Dashboard");
    title->setAlignment(Qt::AlignCenter);

    QLineEdit *inviteCode = new QLineEdit;
    inviteCode->setPlaceholderText("One-time Invitation Code");

    QDateEdit *deadline = new QDateEdit;
    deadline->setCalendarPopup(true);

    QPushButton *generateBtn = new QPushButton("Generate Invitation");
    QPushButton *logoutBtn = new QPushButton("Logout");

    layout->addWidget(title);
    layout->addWidget(inviteCode);
    layout->addWidget(deadline);
    layout->addWidget(generateBtn);
    layout->addWidget(logoutBtn);

    setCentralWidget(widget);

    //connect(logoutBtn, &QPushButton::clicked, this, [this] {stack->setCurrentIndex(0);});

    connect(generateBtn, &QPushButton::clicked, this, [this, deadline, inviteCode]() {
        QString newInviteCode;
        if (deadline->date() < QDate::currentDate()) {
            QMessageBox::warning(this, "Selected Expiration Date Has Passed", inviteCode->text());
        } else {
            newInviteCode = generateInvitation(deadline->date());
        }

        inviteCode->clear();
        inviteCode->setText(newInviteCode);
    });

    connect(logoutBtn, &QPushButton::clicked, this, [this]() {emit logoutRequest();});
}

QString AdminWindow::generateInvitation(const QDate& date) {
    QString failed = "";
    bool isUnique = false;
    QJsonArray loadCodeArray;
    QByteArray bytes;
    //Load Codes
    QFile file("codes.json");

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        bytes = file.readAll();
        file.close();
        QJsonDocument loadDoc = QJsonDocument::fromJson(bytes);
        loadCodeArray = loadDoc.array();
    }

    //End Load

    QDate expirationDate = date;
    int tmpCode;

    while (!isUnique) {
        tmpCode = QRandomGenerator::global()->bounded(1000, 9999);
        isUnique = true;

        for (int i = 0; i < loadCodeArray.size(); i++) {
            QJsonObject loadUserObject = loadCodeArray.at(i).toObject();
            int uniqueCheck = loadUserObject["code"].toInt();

            if (uniqueCheck == tmpCode) {
                isUnique = false;
            }
        }
    }

    QString tmpInviteCode;
    tmpInviteCode = QString::number(tmpCode);

    //Save Codes
    QJsonObject saveCodeObject;

    saveCodeObject["code"] = tmpCode;
    saveCodeObject["expiration"] = expirationDate.toString("yyyy-MM-dd");
    saveCodeObject["status"] = "unused";
    loadCodeArray.append(saveCodeObject);

    QJsonDocument doc(loadCodeArray);
    bytes = doc.toJson();

    if (!file.open(QIODevice::WriteOnly)) return failed;
    file.write(bytes);
    file.close();
    //End Save

    return tmpInviteCode;
}
