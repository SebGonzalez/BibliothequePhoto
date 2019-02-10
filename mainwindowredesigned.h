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

    void refresh_bibliotheque_view();




private:
    Ui::MainWindowRedesigned *ui;
    BibliothequeWidget *bibliothequeWidget;



private slots:

    void load_selection_on_click();
    void import_on_click();





    void on_lineEdit_textEdited(const QString &arg1);
};

#endif // MAINWINDOWREDESIGNED_H
