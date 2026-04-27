#include <QApplication>
#include <QPushButton>
#include <QApplication>
#include "MainWindow.h"
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));//
    a.setStyleSheet("QWidget {background-color: black; color white; }"
    "QLineEdit, QTextEdit { background-color: #1e1e1e; color: white; }"
    "QListWidget { background-color: #1e1e1e; color: white; }"
    "QLabel { color: white; }"
    "QPushButton { color: white; font-size: 14px;} "); //
    MainWindow w;
    w.resize(900, 600);
    w.show();
    return a.exec();
}