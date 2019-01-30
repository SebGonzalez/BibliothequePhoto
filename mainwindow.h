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
#include <QScrollArea>
#include "bibliothequewidget.h"
#include "clickablelabel.h"

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

protected :
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged();

    void handleButton();

    void showTreeView();

    void displayDialogue(QListWidgetItem*);

    void on_treeView_expanded(const QModelIndex &index);

    void multipleSelection(QListWidgetItem*item);

private:
    Ui::MainWindow *ui;
    QPushButton *tag;
    BibliothequeWidget *bibliothequeWigdet;
    bool ctrlIsPressed = false;
    QListWidget listSelect;
};

#endif // MAINWINDOW_H
