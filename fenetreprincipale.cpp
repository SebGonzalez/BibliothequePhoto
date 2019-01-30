#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"


using namespace std;



FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{    
    if(bibliotheque.getImgListSize() == 0) {
        LandingPage *lp = new LandingPage(this);
        lp->exec();
    }

    ui->setupUi(this);

    //Main gallery
    showSelection();


}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

FenetrePrincipale::showSelection() {
    QHBoxLayout *frameLayout = new QHBoxLayout(ui->frame);
    bibliothequeWigdet = new BibliothequeWidget(200,this, &bibliotheque);
    for(unsigned int i = 0; i < selection.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*selection[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);

        bibliothequeWigdet->addPiece(pixmap.scaled(200,200), i);
    }
   frameLayout->addWidget(bibliothequeWigdet);

}
