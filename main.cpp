#include <QApplication>
#include <QPushButton>
#include <QApplication>
#include "qMainWindow.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(900, 600);
    w.show();
    return a.exec();
}