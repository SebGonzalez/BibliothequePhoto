    #include "mainwindowredesigned.h"
#include "ui_mainwindowredesigned.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tagdialog.h"


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

    setMouseTracking(true);
    bibliothequeWidget = new BibliothequeWidget(200,this, &biblio);
    QHBoxLayout *frameLayout = new QHBoxLayout(ui->photo);

    for(unsigned int i = 0; i < biblio.getlisteImage().size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*biblio.getlisteImage()[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
          bibliothequeWidget->addPiece(pixmap.scaled(200,200), biblio.getlisteImage()[i].getId(), biblio.getlisteImage()[i].getTagsString());
    }

   frameLayout->addWidget(bibliothequeWidget);

   connect(ui->bibliButton,SIGNAL(clicked()),this,SLOT(load_selection_on_click()));
   connect(ui->importerButton,SIGNAL(clicked()),this,SLOT(import_on_click()));
   connect(bibliothequeWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(displayViewer(QListWidgetItem*)));

}

MainWindowRedesigned::~MainWindowRedesigned()
{
    cout << "On save les modifs" << endl;
    //Reset file and save all updated data before closing
    biblio.initDataFile();
    for (int i = 0; i < biblio.getImgListSize(); i++) {
        biblio.addToFile(biblio.getlisteImage()[i]);
    }
    delete ui;
}


void MainWindowRedesigned:: refresh_bibliotheque_view(){

    bibliothequeWidget->clear();
    for(unsigned int i = 0; i < biblio.getlisteImage().size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*biblio.getlisteImage()[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
          bibliothequeWidget->addPiece(pixmap.scaled(200,200), biblio.getlisteImage()[i].getId(), biblio.getlisteImage()[i].getTagsString());
    }

}

void MainWindowRedesigned::load_selection_on_click(){


    refresh_bibliotheque_view();
    ui->titre->setText("Ma Bibliothèque");

}


void MainWindowRedesigned:: import_on_click(){

    QStringList mimeTypeFilters;
    mimeTypeFilters << "image/jpeg" << "image/png";
    QFileDialog dialog(this);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    QStringList listeImages = dialog.getOpenFileNames(this,tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.jpeg)"));
    for (int i = 0; i < listeImages.size(); ++i) {
        cout << listeImages.size() << endl;
        Image tmpImage = Image(listeImages[i].toStdString(),biblio.getImgListSize()+i, "NULL");
        biblio.addToFile(tmpImage);
    }
    bibliothequeWidget->clear();
    biblio.deleteImgList();
    biblio.loadImages();
    vector <Image> selection = biblio.getlisteImage();

    for(unsigned int i = 0; i < biblio.getImgListSize(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*selection[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
        bibliothequeWidget->addPiece(pixmap.scaled(200,200), selection[i].getId(), selection[i].getTagsString());
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
                bibliothequeWidget->addPiece(pixmap.scaled(200,200), image_affichees[i].getId(), image_affichees[i].getTagsString());
            }
        }

    }


void MainWindowRedesigned::on_checkBox_stateChanged(int arg1)
{
    for(int i = 0; i < bibliothequeWidget->count(); ++i)
    {
        QListWidgetItem* item = bibliothequeWidget->item(i);
        if(arg1 == 2)
         item->setData(Qt::UserRole+2, "");
        else
           item->setData(Qt::UserRole+2, item->data(Qt::UserRole+3));
    }
}


void MainWindowRedesigned::displayViewer(QListWidgetItem *item)
{
    int idPhoto = item->data(Qt::UserRole+1).toInt();
    int position = biblio.getPositionImage(idPhoto);
     viewer *dialog = new viewer(position, biblio, *bibliothequeWidget);
     dialog->show();
}

void MainWindowRedesigned::on_tagsButton_clicked()
{
    ui->titre->setText("Ma Bibliothèque");
    tagDialog *tag = new tagDialog(biblio);
    tag->exec();
    if( tag->result() == 0 ){
         biblio.deleteTag(tag->chosenDeletedtag.toUtf8().constData());
         image_affichees = biblio.getTaggedImages(tag->chosen_tag.toUtf8().constData());
         if(tag->chosen_tag == "") image_affichees = biblio.getlisteImage();

         bibliothequeWidget->clear();
         for(unsigned int i = 0; i < image_affichees.size(); i++) {
             QPixmap pixmap = QPixmap::fromImage(*image_affichees[i].getQImage());
             pixmap = pixmap.scaledToWidth(200);
             bibliothequeWidget->addPiece(pixmap.scaled(200,200), image_affichees[i].getId(), image_affichees[i].getTagsString());
         }


    }

}

void MainWindowRedesigned::on_Album_pressed()
{
    AlbumDialog *albumDialog = new AlbumDialog(biblio, *bibliothequeWidget);
    albumDialog->exec();

}

void MainWindowRedesigned::on_pushButton_clicked()
{

      ui->titre->setText("Mes favoris");

      image_affichees  = biblio.getFavImages();
      bibliothequeWidget->clear();
      for(unsigned int i = 0; i < image_affichees.size(); i++) {
          QPixmap pixmap = QPixmap::fromImage(*image_affichees[i].getQImage());
          pixmap = pixmap.scaledToWidth(200);
          bibliothequeWidget->addPiece(pixmap.scaled(200,200), image_affichees[i].getId(), image_affichees[i].getTagsString());
      }

}
