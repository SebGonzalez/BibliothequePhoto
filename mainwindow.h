#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <dirent.h>
#include <iostream>
#include <qdebug.h>
#include <QFileSystemModel>
#include <string>
#include "bibliotheque.h"
#include <QScrollArea>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool textChange = false;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged();

    void handleButton();

    void showTreeView();

    void getFics(string path);

    void displayPic(string path);
private:
    Ui::MainWindow *ui;
    QPushButton *tag;
};

#endif // MAINWINDOW_H
