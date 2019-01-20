#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <dirent.h>
#include <iostream>
#include <qdebug.h>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("C:/Users/Theo/Documents/IHM/BibliothequePhoto/PicsTmp")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        printf ("%s\n", ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("Can't Open");
    }


    QPixmap pix("C:/Users/Theo/Documents/IHM/BibliothequePhoto/PicsTmp/Younes.png");
    ui->label->setPixmap(pix.scaled(ui->label->width(),ui->label->height()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(textChange == true){
        tag = new QPushButton(this);
        tag->setText(ui->lineEdit->text());
        ui->formLayout->addWidget(tag);
        //connect(tag, SIGNAL (released()), this, SLOT (handleButton()));
        qDebug() << __FUNCTION__ << "Button created";
    }
}

void MainWindow::handleButton()
{
    tag->setText("Example");
    tag->resize(100,100);
    qDebug() << __FUNCTION__ << "Slot";
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    textChange =true;
}
