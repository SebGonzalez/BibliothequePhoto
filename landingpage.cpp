#include "landingpage.h"
#include "ui_landingpage.h"

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
}

LandingPage::~LandingPage()
{
    delete ui;
}