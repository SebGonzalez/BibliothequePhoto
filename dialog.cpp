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

}


Dialog::Dialog(int position,std::vector<Image> listeImage):
    ui(new Ui::Dialog)
{

    this->liste_image = listeImage;
    this->position = position;
    ui->setupUi(this);
    initLabels();
    QPixmap pixmap = QPixmap::fromImage(*listeImage[position].getQImage());
    ui->current_picture->setPixmap(pixmap);
    indice = position;

    connect(ui->next_photo, SIGNAL(clicked()), this, SLOT(nextImage()));
    connect(ui->previous_photo, SIGNAL(clicked()), this, SLOT(previousImage()) );
    connect(ui->buttonInfo, SIGNAL(clicked()),this, SLOT(displayTags()));


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::initLabels()
{


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
    ui->tagsWidget->setVisible(false);

    ui->next_photo->setAttribute(Qt::WA_Hover);
    ui->previous_photo->setAttribute(Qt::WA_Hover);


}



void Dialog:: nextImage(){

    ui->tagsWidget->setVisible(false);
    QObject* button = QObject::sender();
    if(button == ui->next_photo){
        if(position < this->liste_image.size() - 1){
        position ++;
        QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
        ui->current_picture->setPixmap(pixmap);
        }
    }

 }



void Dialog:: previousImage(){

      ui->tagsWidget->setVisible(false);
      QObject* button = QObject::sender();
      if(button == ui->previous_photo){
          if(position > 0){
           position --;
           QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
           ui->current_picture->setPixmap(pixmap);
          }
      }
}


void Dialog:: displayTags(){
   ui->tagsWidget->setVisible(true);
   std::vector<std::string> tags = liste_image[indice].getTags();
   QString label_tags;
   for(int i = 0 ; i < tags.size() ; i++){
    label_tags = label_tags + tags[i].c_str() +" ";

   }
   ui->tagsWidget->setPlainText(label_tags);
}

