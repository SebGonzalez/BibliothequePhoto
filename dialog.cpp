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
    pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(pixmap);
    indice = position;

    connect(ui->next_photo, SIGNAL(clicked()), this, SLOT(nextImage()));
    connect(ui->previous_photo, SIGNAL(clicked()), this, SLOT(previousImage()) );
    connect(ui->buttonInfo, SIGNAL(clicked()),this, SLOT(displayTags()));
    connect(ui->buttonModify, SIGNAL(clicked()),this, SLOT(rotatePicture()));


}

Dialog::~Dialog()
{
    delete ui;
}

QPixmap Dialog:: resizePixmap(QLabel *label,QPixmap pix){
    QSize labelsize = ui-> current_picture->size();
    return pix.scaled(labelsize, Qt::IgnoreAspectRatio, Qt::FastTransformation);

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


    this->rotate = 0;

    for(int i = 0 ; i < ui->gridLayout->count() ; i++)
        if(!(ui->gridLayout->itemAt(i) == nullptr))
              ui->gridLayout->itemAt(i)->widget()->setVisible(false);



    QObject* button = QObject::sender();
    if(button == ui->next_photo){
        if(position < this->liste_image.size() - 1){
        position ++;

        }
        else {
            position = 0;
        }

        QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
        pixmap = resizePixmap(ui->current_picture,pixmap);
        ui->current_picture->setPixmap(pixmap);
    }

 }



void Dialog:: previousImage(){

    this->rotate = 0;

    for(int i = 0 ; i < ui->gridLayout->count() ; i++)
        if(!(ui->gridLayout->itemAt(i) == nullptr))
              ui->gridLayout->itemAt(i)->widget()->setVisible(false);

    QObject* button = QObject::sender();
      if(button == ui->previous_photo){
          if(position > 0){
           position --;
          }
          else {
              position = this->liste_image.size() - 1;
          }

          QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
          pixmap = resizePixmap(ui->current_picture,pixmap);
          ui->current_picture->setPixmap(pixmap);
      }

}


void Dialog:: displayTags(){

   std::vector<std::string> tags = liste_image[indice].getTags();
   QString label_tags;

   for(int i = 0 ; i < tags.size() ; i++){
     label_tags = tags[i].c_str();
     QPlainTextEdit *label = new QPlainTextEdit();
     label->setPlainText(label_tags);
     label = labelVisualSettings(label);
     ui->gridLayout->addWidget(label,150,i);


   }


}

QPlainTextEdit* Dialog::labelVisualSettings(QPlainTextEdit *label){
    QFont *font = new QFont();
    font->setPointSize(12);
    label->setFont(*font);
    label->setFixedWidth(102);
    label->setFixedHeight(40);
    label->setReadOnly(true);
    label->setBackgroundVisible(true);
    label->setVisible(true);
    return label;

}

void Dialog::rotatePicture(){

    QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
    QMatrix rm;
    this->rotate += 90 % 360;
    rm.rotate(this->rotate);
    pixmap = pixmap.transformed(rm);
    ui->current_picture->setPixmap(pixmap);

}

