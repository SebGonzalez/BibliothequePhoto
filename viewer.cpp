#include "viewer.h"
#include "ui_viewer.h"
#include <iostream>
#include <QLabel>
#include <QPixmap>

using namespace std;
static QImage *original = new QImage("../BibliothequePhoto/firstbackground.jpg");

viewer::viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::viewer)
{
    ui->setupUi(this);

    // Show current picture
    original = new QImage("../BibliothequePhoto/firstbackground.jpg");
    QPixmap pixmap = QPixmap::fromImage(*original);
    ui->current_picture->resize(pixmap.size());
    ui->current_picture->setPixmap(pixmap);

    //info widget
    ui->infoMenu->hide();

}


viewer::viewer(int position, Bibliotheque &bibliotheque, std::vector<Image> listeImage):
    ui(new Ui::viewer)
{

    this->liste_image = listeImage;
    this->position = position;
    ui->setupUi(this);

    QPixmap pixmap = QPixmap::fromImage(*listeImage[position].getQImage());
    ui->current_picture->resize(pixmap.size());
//    pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(pixmap);

    this->bibliotheque = &bibliotheque;
}

viewer::~viewer()
{
    delete ui;
}

/********************
 *        ZOOM      *
 * ******************/
const QSize originalSize = original->size();
static double zoomLevel = 1.0;

void viewer::on_zoom_clicked()
{
    zoomLevel *= 1.25;
    QSize scaled_size = originalSize * zoomLevel;
    QPixmap scaled = QPixmap::fromImage(*original).scaledToWidth(scaled_size.width());
    ui->current_picture->setPixmap(scaled);
}

void viewer::on_zoomOut_clicked()
{
    zoomLevel /= 1.25;
    QSize scaled_size = originalSize * zoomLevel;
    QPixmap scaled = QPixmap::fromImage(*original).scaledToWidth(scaled_size.width());
    ui->current_picture->setPixmap(scaled);
}

/****************************************************************************************/

void viewer::on_rotate_clicked()
{
    QTransform transform;
    QTransform trans = transform.rotate(90);
    original = new QImage(original->transformed(trans));
    ui->current_picture->setPixmap(QPixmap::fromImage(*original));
}

void viewer::on_info_clicked()
{
    QPixmap originalPixmap = QPixmap::fromImage(*original);
    if(ui->infoMenu->isHidden()) {
        ui->infoMenu->show();
        QSize scrollAreaSize = ui->view->size();
        QPixmap scaled = originalPixmap.scaledToWidth(scrollAreaSize.width() * 0.9);
        ui->current_picture->setPixmap(scaled);
    }
    else {
        ui->infoMenu->hide();
        ui->current_picture->setPixmap(originalPixmap);
    }
}
