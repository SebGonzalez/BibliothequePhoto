#ifndef MAINWINDOWREDESIGNED_H
#define MAINWINDOWREDESIGNED_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <dirent.h>
#include <iostream>
#include <qdebug.h>
#include <QFileSystemModel>
#include <string>
#include <QScrollArea>
#include "bibliothequewidget.h"
#include "clickablelabel.h"

namespace Ui {
class MainWindowRedesigned;
}

class MainWindowRedesigned : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRedesigned(QWidget *parent = nullptr);
    ~MainWindowRedesigned();
    void resizeEvent(QResizeEvent* event);
    Bibliotheque bibliotheque;


private:
    Ui::MainWindowRedesigned *ui;
    QPushButton *tag;
    BibliothequeWidget *bibliothequeWigdet;
    QGridLayout *frameLayout;
};

#endif // MAINWINDOWREDESIGNED_H
