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


viewer::viewer(int position, Bibliotheque &bibliotheque):
    ui(new Ui::viewer)
{
    this->bibliotheque = &bibliotheque;
    this->liste_image = this->bibliotheque->getlisteImage();
    this->position = position;
    this->rotate = 90;
    this->originalSize = liste_image[position].getQImage()->size();
    ui->setupUi(this);


    QPixmap current_image = QPixmap::fromImage(*liste_image[position].getQImage());

    ui->current_picture->resize(current_image.size());
//  pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(current_image);


}

viewer::~viewer()
{
    delete ui;
}

/********************
 *        ZOOM      *
 * ******************/

static double zoomLevel = 1.0;

void viewer::on_zoom_clicked()
{
    zoomLevel *= 1.25;
    QSize scaled_size = originalSize * zoomLevel;
    QPixmap scaled = QPixmap::fromImage(*liste_image[position].getQImage()).scaledToWidth(scaled_size.width());
    ui->current_picture->setPixmap(scaled);
}

void viewer::on_zoomOut_clicked()
{
    zoomLevel /= 1.25;
    QSize scaled_size = originalSize * zoomLevel;
    QPixmap scaled = QPixmap::fromImage(*liste_image[position].getQImage()).scaledToWidth(scaled_size.width());
    ui->current_picture->setPixmap(scaled);
}

/****************************************************************************************/

void viewer::on_rotate_clicked()
{
    QTransform transform;
    QTransform trans = transform.rotate(this->rotate);
    QImage *rotated_image = new QImage(*liste_image[position].getQImage());
    QImage *current_picture = new QImage(rotated_image->transformed(trans));
    ui->current_picture->setPixmap(QPixmap::fromImage(*current_picture));
    this->rotate += 90 % 360;
}

void viewer::on_info_clicked()
{
    QPixmap originalPixmap = QPixmap::fromImage(*liste_image[position].getQImage());
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

void viewer::on_next_picture_clicked()
{
    this->rotate = 90;
    if(position < this->liste_image.size() - 1){
    position ++;

    }
    else {
        position = 0;
    }

    QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
    ui->current_picture->setPixmap(pixmap);


}

void viewer::on_previous_picture_clicked()
{
    this->rotate = 90;
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

