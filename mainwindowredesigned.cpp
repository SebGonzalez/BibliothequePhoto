#include "mainwindowredesigned.h"
#include "ui_mainwindowredesigned.h"
#include "tagdialog.h"
#include "bibliotheque.h"
#include "landingpage.h"
#include "image.h"
#include <QFileDialog>
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

    if(getEmptyBibliotheque() == true){
        LandingPage *lp = new LandingPage(&biblio);
        lp->exec();
        biblio.loadImages();
        if( biblio.getlisteImage().size() == 0) {
           return;
       }

    }


    ui->setupUi(this);

    image_affichees = biblio.getlisteImage();

    setMouseTracking(true);
    bibliothequeWidget = new BibliothequeWidget(200,this, &biblio);
    QHBoxLayout *frameLayout = new QHBoxLayout(ui->photo);

    for(unsigned int i = 0; i < biblio.getlisteImage().size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*biblio.getlisteImage()[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        bibliothequeWidget->addPiece(pixmap.scaled(200,200), biblio.getlisteImage()[i].getId(), biblio.getlisteImage()[i].getTagsString());
    }

   frameLayout->addWidget(bibliothequeWidget);

   connect(ui->bibliButton,SIGNAL(clicked()),this,SLOT(load_selection_on_click()));
   connect(ui->importerButton,SIGNAL(clicked()),this,SLOT(import_on_click()));
   connect(bibliothequeWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(displayViewer(QListWidgetItem*)));
   connect(ui->favButton, SIGNAL(clicked()), this, SLOT(on_favButton_clicked()));

   ui->selectionSize->hide();
   ui->titre->setText("Ma Bibliothèque");
   string nbPhotos = "contient " + std::to_string(biblio.getlisteImage().size()) + " images.";
   ui->selectionSize->setText(QString::fromStdString(nbPhotos));
}

MainWindowRedesigned::~MainWindowRedesigned()
{
    //Reset file and save all updated data before closing
    biblio.initDataFile();
    for (int i = 0; i < biblio.getImgListSize(); i++) {
        biblio.addToFile(biblio.getlisteImage()[static_cast<unsigned int>(i)]);
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
    biblio.fav_window = false;

}

void MainWindowRedesigned:: import_on_click(){

    QStringList mimeTypeFilters;
    mimeTypeFilters << "imadiagramme de navigation ihm exemplege/jpeg" << "image/png";
    QFileDialog dialog(this);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    QStringList listeImages = dialog.getOpenFileNames(this,tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.jpeg)"));
    for (int i = 0; i < listeImages.size(); ++i) {
        Image tmpImage = Image(listeImages[i].toStdString(),biblio.getImgListSize()+i, "NULL", 0);
        biblio.addToFile(tmpImage);
    }
    bibliothequeWidget->clear();
    biblio.deleteImgList();
    biblio.loadImages();
    vector <Image> selection = biblio.getlisteImage();

    for(unsigned int i = 0; i < static_cast<unsigned int>(biblio.getImgListSize()); i++) {
        QPixmap pixmap = QPixmap::fromImage(*selection[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        bibliothequeWidget->addPiece(pixmap.scaled(200,200), selection[i].getId(), selection[i].getTagsString());
    }

}


void MainWindowRedesigned::on_lineEdit_textEdited(const QString &arg1)
{

    image_affichees = biblio.getTaggedImages(ui->lineEdit->text().toStdString());
    if(image_affichees.size() != 0) {
        bibliothequeWidget->clear();
        for(unsigned int i = 0; i < image_affichees.size(); i++) {
            QPixmap pixmap = QPixmap::fromImage(*image_affichees[i].getQImage());
            pixmap = pixmap.scaledToWidth(200);
            bibliothequeWidget->addPiece(pixmap.scaled(200,200), image_affichees[i].getId(), image_affichees[i].getTagsString());
            string nbPhotos = "contient " + std::to_string(image_affichees.size()) + " images.";
            ui->selectionSize->setText(QString::fromStdString(nbPhotos));
            ui->titre->setText(QString::fromStdString("Résultat de recherche du filtre \"" + arg1.toStdString() + "\""));

        }
     }

    if(arg1.compare("") == 0) {
        image_affichees = biblio.getlisteImage();
        bibliothequeWidget->clear();
        for(unsigned int i = 0; i < image_affichees.size(); i++) {
            QPixmap pixmap = QPixmap::fromImage(*image_affichees[i].getQImage());
            pixmap = pixmap.scaledToWidth(200);
            bibliothequeWidget->addPiece(pixmap.scaled(200,200), image_affichees[i].getId(), image_affichees[i].getTagsString());
            string nbPhotos = "contient " + std::to_string(image_affichees.size()) + " images.";
        }
        string nbPhotos = "contient " + std::to_string(image_affichees.size()) + " images.";
        ui->selectionSize->setText(QString::fromStdString(nbPhotos));
        ui->titre->setText("Ma Bibliothèque");

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
    viewer *dialog;

    if(biblio.fav_window == true){
        position = biblio.position_from_list(biblio.getFavImages(),idPhoto);
        dialog = new viewer(position, biblio, *bibliothequeWidget,biblio.getFavImages());
    }
    else
         dialog = new viewer(position, biblio, *bibliothequeWidget);

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

    if(tag->chosen_tag.compare("")){
        ui->titre->setText("Résultat de recherche du filtre \"" + tag->chosen_tag + "\"");
        ui->selectionSize->setText(QString::fromStdString("contient " + std::to_string(image_affichees.size()) + " images."));
        if(image_affichees.size() == 1)   ui->selectionSize->setText(QString::fromStdString("contient " + std::to_string(image_affichees.size()) + " image."));
    }

}

void MainWindowRedesigned::on_Album_pressed()
{

    AlbumDialog *albumDialog = new AlbumDialog(biblio, *bibliothequeWidget);
    albumDialog->exec();

}



bool MainWindowRedesigned::getEmptyBibliotheque(){

if(biblio.getImgListSize() == 0)
    return true;

return false;

}



void MainWindowRedesigned::on_favButton_clicked()
{
    biblio.fav_window = true;
    ui->titre->setText("Mes favoris");

    image_affichees  = biblio.getFavImages();
    bibliothequeWidget->clear();
    for(unsigned int i = 0; i < image_affichees.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*image_affichees[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        bibliothequeWidget->addPiece(pixmap.scaled(200,200), image_affichees[i].getId(), image_affichees[i].getTagsString());
    }
}
