#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bibliotheque.h"
#include "dialog.h"

#include <QPixmap>
#include <iostream>
#include <qdebug.h>

using namespace std;

    Bibliotheque bibliotheque;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(1600,900);
    ui->setupUi(this);



    displayPic("PicsTmp/Younes.png");
    getFics("PicsTmp/");
    showTreeView();

    QWidget *w = new QWidget;
    w->setLayout(ui->presentateurPhoto);
    ui->scrollArea->setWidget(w);

    bibliotheque.drawImages(ui->presentateurPhoto);

    for(int i = 0 ; i < bibliotheque.getImgListSize() ; i++)
        connect(ui->presentateurPhoto->itemAt(i)->widget(), SIGNAL(clicked()),SLOT(displayDialogue()));




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayPic(string path)
{
    QPixmap pix;
    pix.load(path.c_str());
    ui->label->setPixmap(pix.scaled(ui->label->width(),ui->label->height()));

}

void MainWindow::getFics(string path)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
          string str(ent->d_name);
          if(str.find('png') != string::npos)
            printf ("%s\n", ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("Can't Open");
    }
}

void MainWindow::showTreeView()
{
    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());
    ui->treeView->setModel(model);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
}

void MainWindow::on_pushButton_clicked()
{
    if(textChange == true){
        tag = new QPushButton(this);
        tag->setText(ui->lineEdit->text());
        ui->formLayout->addWidget(tag);
        //connect(tag, SIGNAL (released()), this, SLOT (handleButton()));
        //qDebug() << __FUNCTION__ << "Button created";
    }
}



void MainWindow::handleButton()
{
    tag->setText("Example");
    tag->resize(100,100);
   // qDebug() << __FUNCTION__ << "Slot";
}

void MainWindow::on_lineEdit_textChanged()
{
    textChange =true;
}


void MainWindow::displayDialogue(){

    for(int i = 0 ; i < bibliotheque.getImgListSize();i++){
        QObject* widget = QObject::sender();
        if(widget == ui->presentateurPhoto->itemAt(i)->widget()){
            Dialog *dialog = new Dialog(i,bibliotheque.getlisteImage());

         //    Dialog *dialog = new Dialog();
            dialog->exec();
        }
    }




}
