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


Dialog::Dialog(int position, Bibliotheque &bibliotheque, std::vector<Image> listeImage):
    ui(new Ui::Dialog)
{

    this->liste_image = listeImage;
    this->position = position;
    ui->setupUi(this);
    initLabels();

    QPixmap pixmap = QPixmap::fromImage(*listeImage[position].getQImage());
    ui->current_picture->resize(pixmap.size());
//    pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(pixmap);
    indice = position;

    connect(ui->next_photo, SIGNAL(clicked()), this, SLOT(nextImage()));
    connect(ui->previous_photo, SIGNAL(clicked()), this, SLOT(previousImage()) );
    connect(ui->buttonInfo, SIGNAL(clicked()),this, SLOT(displayTags()));
    connect(ui->buttonRotate, SIGNAL(clicked()),this, SLOT(rotatePicture()));
    connect(ui->buttonModify, SIGNAL(clicked()),this, SLOT(modifierTags()));
    connect(ui->buttonValidate, SIGNAL(clicked()),this, SLOT(validateModifications()));

    this->bibliotheque = &bibliotheque;
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
    ui->buttonRotate->setIcon(style.standardIcon(QStyle::SP_BrowserReload));


    ui->buttonThrow->resize(45,45);
    ui->buttonInfo->resize(45,45);
    ui->next_photo->resize(100,75);
    ui->previous_photo->resize(100,75);
    ui->buttonRotate->resize(45,45);



}


void Dialog:: nextImage(){


    this->rotate = 0;

    for (int i = 0; i < ui->gridLayout->count(); i++)
         ui->gridLayout->itemAt(i)->widget()->deleteLater();



    QObject* button = QObject::sender();
    if(button == ui->next_photo){
        if(position < this->liste_image.size() - 1){
        position ++;

        }
        else {
            position = 0;
        }

        QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
        ui->current_picture->resize(pixmap.size());
        ui->current_picture->setPixmap(pixmap);
    }

 }



void Dialog:: previousImage(){

    this->rotate = 0;

    for (int i = 0; i < ui->gridLayout->count(); i++)
         ui->gridLayout->itemAt(i)->widget()->deleteLater();

    QObject* button = QObject::sender();
      if(button == ui->previous_photo){
          if(position > 0){
           position --;
          }
          else {
              position = this->liste_image.size() - 1;
          }

          QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
          ui->current_picture->resize(pixmap.size());
          ui->current_picture->setPixmap(pixmap);
      }

}


void Dialog:: displayTags(){

    for (int i = 0; i < ui->gridLayout->count(); i++)
          ui->gridLayout->itemAt(i)->widget()->deleteLater();


   std::vector<std::string> tags = liste_image[position].getTags();
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
    label->setFixedWidth(250);
    label->setFixedHeight(40);
    label->setReadOnly(true);
    label->setBackgroundVisible(true);
    label->setVisible(true);
    return label;

}

void Dialog::rotatePicture(){

    QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
    QMatrix rm;
    this->rotate += 90 ;
    rm.rotate(this->rotate);
    pixmap = pixmap.transformed(rm);
    ui->current_picture->resize(pixmap.size());
    ui->current_picture->setPixmap(pixmap);

}


void Dialog::on_buttonThrow_pressed()
{
    bibliotheque->removeImage(this->liste_image[this->position].getId());
    liste_image.erase(liste_image.begin() + position);

    if(position == static_cast<int>(liste_image.size())) {
        position--;
    }
    QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
    pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(pixmap);
}


void Dialog::modifierTags(){

    QList<QPlainTextEdit *> list = this -> findChildren<QPlainTextEdit *> ();
    for(int i = 0 ; i < ui->gridLayout->count() ; i++){
        if(list[i] != nullptr)
            list[i]->setReadOnly(false);
    }
}


void Dialog::validateModifications(){

    QList<QPlainTextEdit *> list = this -> findChildren<QPlainTextEdit *> ();
    for(int i = 0 ; i < ui->gridLayout->count() ; i++){
        if(list[i] != nullptr)

             list[i]->setPlainText(list[i]->toPlainText());
    }


    for(int i = 0 ; i < ui->gridLayout->count(); i++){

        std::string texte = list[i]->toPlainText().toUtf8().constData();
        liste_image[indice].setTag(i,texte);
        bibliotheque->setTagsListeImage(indice,i,texte);
    }
}

