#include "landingpage.h"
#include "ui_landingpage.h"
#import "QFileDialog"
#include "image.h"

LandingPage::LandingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LandingPage)
{
    this->setFixedSize(800, 534);
    ui->setupUi(this);

    //Backgound image
    QPixmap bkgnd("../BibliothequePhoto/firstbackground.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    connect(ui->importer, SIGNAL(clicked()), this, SLOT(displayMainWindow()));
}

LandingPage::LandingPage(Bibliotheque *biblio) : ui(new Ui::LandingPage){


    this->setFixedSize(800, 534);
    ui->setupUi(this);
    this->bibliotheque = biblio;

    //Backgound image
    QPixmap bkgnd("../BibliothequePhoto/firstbackground.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    connect(ui->importer, SIGNAL(clicked()), this, SLOT(displayMainWindow()));

}
LandingPage::~LandingPage()
{
    delete ui;
}

void LandingPage::displayMainWindow(){

    this->close();
}



void LandingPage::on_importer_clicked()
{
    QStringList mimeTypeFilters;
    mimeTypeFilters << "imadiagramme de navigation ihm exemplege/jpeg" << "image/png";
    QFileDialog dialog(this);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    QStringList listeImages = dialog.getOpenFileNames(this,tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.jpeg)"));
    for (int i = 0; i < listeImages.size(); ++i) {
        Image tmpImage = Image(listeImages[i].toStdString(),bibliotheque->getImgListSize()+i, "NULL", 0);
        bibliotheque->addToFile(tmpImage);
        }


}
