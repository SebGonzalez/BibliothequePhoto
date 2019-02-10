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

MainWindowRedesigned::MainWindowRedesigned(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRedesigned)
{
    ui->setupUi(this);

    image_affichees = biblio.getlisteImage();
    QHBoxLayout *frameLayout = new QHBoxLayout(ui->selection);
    BibliothequeWidget *bibliothequeWidget = new BibliothequeWidget(200,this, &biblio);
    for(unsigned int i = 0; i < image_affichees.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*image_affichees[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        pixmap.scaledToHeight(200);
        bibliothequeWidget->addPiece(pixmap.scaled(200,200), image_affichees[i].getId());
    }


    frameLayout->addWidget(bibliothequeWidget);

    connect(ui->bibliButton,SIGNAL(clicked()),this,SLOT(load_selection_on_click()));
    connect(ui->importerButton,SIGNAL(clicked()),this,SLOT(import_on_click()));

}

MainWindowRedesigned::~MainWindowRedesigned()
{
    delete ui;
}



void MainWindowRedesigned::load_selection_on_click(){







}

void MainWindowRedesigned:: import_on_click(){

   QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.jpeg)"));
   Image *imported_image = new Image(fileName.toStdString(), 0);
   biblio.addImage(*imported_image);
   std::cout << "Image ajoutée" << endl;

}
