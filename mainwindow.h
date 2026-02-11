//
// Created by Luka Powers on 2/8/26.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
    MainWindow(QWidget *parent = nullptr);

private:
    QMenu *menu;
    QMenu *helpMenu;
    QMenu *settingsMenu;
    QMenu *myName;
};

#endif //MAINWINDOW_H
