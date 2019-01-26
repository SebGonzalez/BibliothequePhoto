#include "dialog.h"
#include "ui_dialog.h"
#include <QPixmap>
#include <QCommonStyle>
#include "global_variables.h"
#include <QHoverEvent>

QStringList pictures_array;
int indice;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    loadImagesfromList();
    initLabels();
     QPixmap pix1(pictures_array.at(0));
     ui->current_picture->setPixmap(pix1);

     indice = 0;

     connect(ui->next_photo, SIGNAL(clicked()), this, SLOT(nextImage()));
     connect(ui->previous_photo, SIGNAL(clicked()), this, SLOT(previousImage()) );



}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::initLabels(    )
{
    this->setMouseTracking(true);
    ui->next_photo->setMouseTracking(true);

    QCommonStyle style;
    ui->previous_photo->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->next_photo->setIcon(style.standardIcon(QStyle::SP_ArrowRight));
    ui->buttonThrow->setIcon(style.standardIcon(QStyle::SP_TrashIcon));
    ui->buttonInfo->setIcon(style.standardIcon(QStyle::SP_FileDialogInfoView));
    ui->buttonModify->setIcon(style.standardIcon(QStyle::SP_BrowserReload));

    ui->buttonThrow->resize(45,45);
    ui->buttonInfo->resize(45,45);
    ui->next_photo->resize(100,75);
    ui->previous_photo->resize(100,75);
    ui->buttonModify->resize(45,45);

    ui->next_photo->setAttribute(Qt::WA_Hover);
    ui->previous_photo->setAttribute(Qt::WA_Hover);

    //ui->next_photo->hide();
    //ui->previous_photo->hide();

}

void Dialog::loadImagesfromList()
{

     pictures_array.append("/home/amine/Documents/IHM/ON_CLICK_VIEW/PicsTmp/1.jpg");
      pictures_array.append("/home/amine/Documents/IHM/ON_CLICK_VIEW/PicsTmp/2.jpg");
       pictures_array.append("/home/amine/Documents/IHM/ON_CLICK_VIEW/PicsTmp/3.jpg");
        pictures_array.append("/home/amine/Documents/IHM/ON_CLICK_VIEW/PicsTmp/4.jpg");
         pictures_array.append("/home/amine/Documents/IHM/ON_CLICK_VIEW/PicsTmp/5.jpg");



}



void Dialog:: nextImage(){
    QObject* button = QObject::sender();
    if(button == ui->next_photo){
        if(indice < pictures_array.size() - 1){
        indice ++;
        QPixmap pix1(pictures_array.at(indice));
        ui->current_picture->setPixmap(pix1);
        }
    }

 }



void Dialog:: previousImage(){

      QObject* button = QObject::sender();
      if(button == ui->previous_photo){
          if(indice > 0){
           indice --;
           QPixmap pix2(pictures_array.at(indice));
           ui->current_picture->setPixmap(pix2);
          }
      }

}


