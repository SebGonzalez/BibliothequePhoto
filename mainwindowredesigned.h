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

    Bibliotheque bibliotheque;
    QPushButton *tag;
    BibliothequeWidget *bibliothequeWigdet;
    QGridLayout *frameLayout;

public:
    explicit MainWindowRedesigned(QWidget *parent = nullptr);
    ~MainWindowRedesigned();




private:
    Ui::MainWindowRedesigned *ui;


private slots:

    void load_selection_on_click();
    void import_on_click();





};

#endif // MAINWINDOWREDESIGNED_H
