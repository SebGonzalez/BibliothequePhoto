#include "mainwindowredesigned.h"
#include "ui_mainwindowredesigned.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "bibliotheque.h"
#include "dialog.h"
#include "landingpage.h"
#include "image.h"

#include <QFileDialog>

 Bibliotheque biblio;
 vector<Image> image_affichees;

#include "viewer.h"

#include <QPixmap>
#include <iostream>
#include <qdebug.h>
#include <QGuiApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QGridLayout>

using namespace std;


MainWindowRedesigned::MainWindowRedesigned(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRedesigned)
{
    ui->setupUi(this);

    image_affichees = biblio.getlisteImage();

    bibliothequeWidget = new BibliothequeWidget(200,this, &biblio);
    QHBoxLayout *frameLayout = new QHBoxLayout(ui->photo);

    for(unsigned int i = 0; i < biblio.getlisteImage().size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*biblio.getlisteImage()[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
          bibliothequeWidget->addPiece(pixmap.scaled(200,200), biblio.getlisteImage()[i].getId());
    }

   frameLayout->addWidget(bibliothequeWidget);


   connect(ui->bibliButton,SIGNAL(clicked()),this,SLOT(load_selection_on_click()));
   connect(ui->importerButton,SIGNAL(clicked()),this,SLOT(import_on_click()));
}


void MainWindowRedesigned:: refresh_bibliotheque_view(){

    bibliothequeWidget->clear();
    for(unsigned int i = 0; i < biblio.getlisteImage().size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*biblio.getlisteImage()[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
          bibliothequeWidget->addPiece(pixmap.scaled(200,200), biblio.getlisteImage()[i].getId());
    }

}


MainWindowRedesigned::~MainWindowRedesigned()
{
    delete ui;
}




void MainWindowRedesigned::load_selection_on_click(){

    refresh_bibliotheque_view();


}


void MainWindowRedesigned:: import_on_click(){


    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.jpeg)"));
    if(fileName != nullptr){

       Image *imported_image = new Image(fileName.toStdString(), 0);
       biblio.addImage(*imported_image);
       refresh_bibliotheque_view();
    }


}


void MainWindowRedesigned::on_lineEdit_textEdited(const QString &arg1)
{

    image_affichees = biblio.getTaggedImages(ui->lineEdit->text().toStdString());
    if(arg1 == "") {
        image_affichees = biblio.getlisteImage();
    }

    if(image_affichees.size() != 0) {

            bibliothequeWidget->clear();
            for(unsigned int i = 0; i < image_affichees.size(); i++) {
                QPixmap pixmap = QPixmap::fromImage(*image_affichees[i].getQImage());
                pixmap = pixmap.scaledToWidth(200);
                bibliothequeWidget->addPiece(pixmap.scaled(200,200), image_affichees[i].getId());
            }
        }

    }


void MainWindowRedesigned::on_checkBox_stateChanged(int arg1)
{
    cout << arg1 << endl;
    for(int i = 0; i < bibliothequeWidget->count(); ++i)
    {
        QListWidgetItem* item = bibliothequeWidget->item(i);
        if(arg1 == 2)
         item->setData(Qt::UserRole+2, "");
        else
           item->setData(Qt::UserRole+2, item->data(Qt::UserRole+3));
    }
}
