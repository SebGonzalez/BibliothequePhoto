    #include "viewer.h"
#include "ui_viewer.h"
#include <iostream>
#include <QLabel>
#include <QPixmap>
#include <QComboBox>

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


viewer::viewer(int position, Bibliotheque &bibliotheque, BibliothequeWidget &bibliothequeWidget):
    ui(new Ui::viewer)
{
    this->bibliotheque = &bibliotheque;
    this->bibliothequeWidget = &bibliothequeWidget;
    this->liste_image = this->bibliotheque->getlisteImage();
    this->position = position;
    this->rotate = 90;
    this->originalSize = liste_image[position].getQImage()->size();
    ui->setupUi(this);


    QPixmap current_image = QPixmap::fromImage(*liste_image[position].getQImage());

    ui->current_picture->resize(current_image.size());
//  pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(current_image);

    //info widget
    ui->infoMenu->hide();
}

viewer::viewer(int position, Bibliotheque &bibliotheque, BibliothequeWidget &bibliothequeWidget,std::vector<Image> liste_image):
    ui(new Ui::viewer)
{
    this->bibliotheque = &bibliotheque;
    this->bibliothequeWidget = &bibliothequeWidget;
    this->liste_image = liste_image;
    this->position = position;
    this->rotate = 90;
    this->originalSize = liste_image[position].getQImage()->size();
    ui->setupUi(this);


    QPixmap current_image = QPixmap::fromImage(*liste_image[position].getQImage());

    ui->current_picture->resize(current_image.size());
//  pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(current_image);

    //info widget
    ui->infoMenu->hide();
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
    QSize scaled_size = this->originalSize * zoomLevel;
    QPixmap scaled = QPixmap::fromImage(*liste_image[position].getQImage()).scaledToWidth(scaled_size.width());
    ui->current_picture->setPixmap(scaled);
}

void viewer::on_zoomOut_clicked()
{
    zoomLevel /= 1.25;
    QSize scaled_size = this->originalSize * zoomLevel;
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
    QSize scaled_size = this->originalSize * zoomLevel;
    ui->current_picture->setPixmap(QPixmap::fromImage(*current_picture).scaledToWidth(scaled_size.width()));
    this->rotate += 90 % 360;
}

void viewer::on_info_clicked()
{
    QPixmap originalPixmap = QPixmap::fromImage(*liste_image[position].getQImage());
    if(ui->infoMenu->isHidden()) {
        ui->infoMenu->show();


        /**************************************************************
         *                          Infobar data
         * ************************************************************/
        Image thisImage = liste_image[position];
        //Show filename
        //TODO Parse only filename without exception to allow modification
        ui->filename->setText(QString::fromStdString(thisImage.getChemin()));
        //Show size
        QFile file(QString::fromStdString(thisImage.getChemin()));
        string stringSize = std::to_string(file.size() / 1000);
        ui->size->setText(QString::fromStdString(stringSize) + " ko");
        //Show dimensions
        string height = std::to_string(thisImage.getQImage()->height());
        string width  = std::to_string(thisImage.getQImage()->width ());
        ui->dimensions->setText(QString::fromStdString(height + "x" + width));


        /**************************************************************
         *                          Tags in infobar
         * ************************************************************/

        //Create lineEdit for each tag
        QWidget *tags = new QWidget(ui->tagScrollArea);
        //ui->tagScrollArea->setStyleSheet("background : transparent");
        tags->setLayout(new QVBoxLayout());
        for (int i = 0; i < thisImage.getTags().size(); i++) {
            QLineEdit *tag = new QLineEdit(tags);
            string currentTag  = thisImage.getTags()[i];
            tag->setText(QString::fromStdString(currentTag));
            tags->layout()->addWidget(tag);
            cout << thisImage.getTags()[i] << endl;
        }
        //TODO Spacer in tagScrollArea
//        QObject *spacer = ui->tagScrollArea->children()[0];
        ui->tagScrollArea->setWidget(tags);

        //New link for add tag
        QWidget *addTag = new QWidget(ui->tagScrollArea);
        QPushButton *addTagButton = new QPushButton(addTag);
        addTagButton->setText("Ajouter un tag");
        connect(addTagButton,SIGNAL(clicked()),this,SLOT(on_addTag_clicked()));
        QComboBox *cb = new QComboBox(ui->tagScrollArea);
        tags->layout()->addWidget(addTag);
        tags->layout()->addWidget(cb);

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

    updateInfoBar();
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

    updateInfoBar();
}

void viewer::updateInfoBar() {
    if (ui->infoMenu->isHidden()) {
        on_info_clicked();
        ui->infoMenu->hide();
    }
    else {
        ui->infoMenu->hide();
        on_info_clicked();
    }
}


void viewer::on_boutonSupprimer_pressed()
{
    bibliotheque->removeImage(this->liste_image[this->position].getId());
    liste_image.erase(liste_image.begin() + position);

    if(position == static_cast<int>(liste_image.size())) {
        position--;
    }
    QPixmap pixmap = QPixmap::fromImage(*liste_image[position].getQImage());
    ui->current_picture->resize(pixmap.size());
    ui->current_picture->setPixmap(pixmap);

    this->bibliothequeWidget->refreshView();

}

void viewer::on_quitButton_clicked()
{
    on_info_clicked();
}

void viewer::on_addTag_clicked(){
 QObject* button = QObject::sender();

}
