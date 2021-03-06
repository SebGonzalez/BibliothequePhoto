#include "viewer.h"
#include "ui_viewer.h"
#include <iostream>
#include <QLabel>
#include <QPixmap>
#include <QComboBox>
#include <QLineEdit>
#include <QStandardItemModel>
#include <algorithm>
#include "confirmdelete.h"
#include "ajouttagdialog.h"
#include "image.h"

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
    this->originalSize = liste_image[static_cast<unsigned int>(position)].getQImage()->size();
    ui->setupUi(this);

    QMainWindow::setWindowTitle(QString::fromStdString(this->liste_image[static_cast<unsigned int>(this->position)].getChemin()));

    QPixmap current_image = QPixmap::fromImage(*liste_image[static_cast<unsigned int>(position)].getQImage());

    ui->current_picture->resize(current_image.size());
//  pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(current_image);

    //info widget
    ui->infoMenu->hide();

    //icons
    //Zoom in
    QPixmap pixmap("../BibliothequePhoto/icons/zoom-in.png");
    QIcon ButtonIcon(pixmap);
    ui->zoom->setIcon(ButtonIcon);

    //Zoom out
    QPixmap pixmap2("../BibliothequePhoto/icons/zoom-out.png");
    QIcon ButtonIcon2(pixmap2);
    ui->zoomOut->setIcon(ButtonIcon2);

    //Rotate
    QPixmap pixmap3("../BibliothequePhoto/icons/rotate.svg");
    QIcon ButtonIcon3(pixmap3);
    ui->rotate->setIcon(ButtonIcon3);

    //Delete
    QPixmap pixmap4("../BibliothequePhoto/icons/delete.svg");
    QIcon ButtonIcon4(pixmap4);
    ui->deleteButton->setIcon(ButtonIcon4);

    //Info
    QPixmap pixmap5("../BibliothequePhoto/icons/info.svg");
    QIcon ButtonIcon5(pixmap5);
    ui->info->setIcon(ButtonIcon5);

    //Favori
    if (this->liste_image[static_cast<unsigned int>(this->position)].getFav() == 0) {
        QPixmap pixmap6("../BibliothequePhoto/icons/star.svg");
        QIcon ButtonIcon6(pixmap6);
        ui->favourite->setIcon(ButtonIcon6);
    }
    else {
        QPixmap pixmap6("../BibliothequePhoto/icons/star-filled.svg");
        QIcon ButtonIcon6(pixmap6);
        ui->favourite->setIcon(ButtonIcon6);
    }


    //button->setIconSize(pixmap.rect().size());
}

viewer::viewer(int position, Bibliotheque &bibliotheque, BibliothequeWidget &bibliothequeWidget,std::vector<Image> liste_image):
    ui(new Ui::viewer)
{
    this->bibliotheque = &bibliotheque;
    this->bibliothequeWidget = &bibliothequeWidget;
    this->liste_image = liste_image;
    this->position = position;
    this->rotate = 90;
    this->originalSize = liste_image[static_cast<unsigned long>(position)].getQImage()->size();
    ui->setupUi(this);


    QPixmap current_image = QPixmap::fromImage(*liste_image[static_cast<unsigned int>(position)].getQImage());

    ui->current_picture->resize(current_image.size());
//  pixmap = resizePixmap(ui->current_picture,pixmap);
    ui->current_picture->setPixmap(current_image);

    //info widget
    ui->infoMenu->hide();
    //icons
    //Zoom in
    QPixmap pixmap("../BibliothequePhoto/icons/zoom-in.png");
    QIcon ButtonIcon(pixmap);
    ui->zoom->setIcon(ButtonIcon);

    //Zoom out
    QPixmap pixmap2("../BibliothequePhoto/icons/zoom-out.png");
    QIcon ButtonIcon2(pixmap2);
    ui->zoomOut->setIcon(ButtonIcon2);

    //Rotate
    QPixmap pixmap3("../BibliothequePhoto/icons/rotate.svg");
    QIcon ButtonIcon3(pixmap3);
    ui->rotate->setIcon(ButtonIcon3);

    //Delete
    QPixmap pixmap4("../BibliothequePhoto/icons/delete.svg");
    QIcon ButtonIcon4(pixmap4);
    ui->deleteButton->setIcon(ButtonIcon4);

    //Info
    QPixmap pixmap5("../BibliothequePhoto/icons/info.svg");
    QIcon ButtonIcon5(pixmap5);
    ui->info->setIcon(ButtonIcon5);

    //Favori
    if (this->liste_image[static_cast<unsigned int>(this->position)].getFav() == 0) {
        QPixmap pixmap6("../BibliothequePhoto/icons/star.svg");
        QIcon ButtonIcon6(pixmap6);
        ui->favourite->setIcon(ButtonIcon6);
    }
    else {
        QPixmap pixmap6("../BibliothequePhoto/icons/star-filled.svg");
        QIcon ButtonIcon6(pixmap6);
        ui->favourite->setIcon(ButtonIcon6);
    }
}

viewer::~viewer()
{
    delete ui;
}

/*****************************************************************************************
 *                                         ZOOM                                          *
 *****************************************************************************************/

static double zoomLevel = 1.0;

void viewer::on_zoom_clicked()
{
    zoomLevel *= 1.25;
    QSize scaled_size = this->originalSize * zoomLevel;
    QPixmap scaled = QPixmap::fromImage(*liste_image[static_cast<unsigned int>(position)].getQImage()).scaledToWidth(scaled_size.width());
    ui->current_picture->setPixmap(scaled);
}

void viewer::on_zoomOut_clicked()
{
    zoomLevel /= 1.25;
    QSize scaled_size = this->originalSize * zoomLevel;
    QPixmap scaled = QPixmap::fromImage(*liste_image[static_cast<unsigned int>(position)].getQImage()).scaledToWidth(scaled_size.width());
    ui->current_picture->setPixmap(scaled);
}

/*****************************************************************************************
 *                                         ROTATION                                      *
 *****************************************************************************************/

void viewer::on_rotate_clicked()
{
    QTransform transform;
    QTransform trans = transform.rotate(this->rotate);
    QImage *rotated_image = new QImage(*liste_image[static_cast<unsigned int>(position)].getQImage());
    QImage *current_picture = new QImage(rotated_image->transformed(trans));
    QSize scaled_size = this->originalSize * zoomLevel;
    ui->current_picture->setPixmap(QPixmap::fromImage(*current_picture).scaledToWidth(scaled_size.width()));
    this->rotate += 90 % 360;
}

/*****************************************************************************************
 *                                     INFOBAR                                           *
 *****************************************************************************************/

void viewer::on_info_clicked()
{
    QPixmap originalPixmap = QPixmap::fromImage(*liste_image[static_cast<unsigned int>(position)].getQImage());
    if(ui->infoMenu->isHidden()) {
        ui->infoMenu->show();

        /**************************************************************
         *                          Infobar data
         * ************************************************************/
        Image thisImage = liste_image[static_cast<unsigned int>(position)];
        //Show filename
        string fullpath = thisImage.getChemin();
        unsigned long long lastSlash = fullpath.find_last_of('/');
        unsigned long long extension = fullpath.find_last_of('.');
        string filename = fullpath.substr(0            , extension);
               filename = filename.substr(lastSlash + 1, filename.size());
        ui->filename->setText(QString::fromStdString(filename));

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
        tags = new QWidget(ui->tagScrollArea);
        ui->tagScrollArea->setStyleSheet("background : transparent");
        tags->setLayout(new QVBoxLayout());
        tags->layout()->setAlignment(Qt::AlignTop);
        tag.clear();
        for (unsigned int i = 0; i < thisImage.getTags().size(); i++) {
            tag.push_back(new QLabel(tags));
            string currentTag = thisImage.getTags()[i];
            tag[i]->setText(QString::fromStdString(currentTag));
            //connect(tag[i], SIGNAL(editingFinished()), this, SLOT(on_tag_editingFinished(i)));
            tags->layout()->addWidget(tag[i]);
        }

        //New link for add tag
        addTagButton = new QPushButton();
        addTagButton->setText("Ajouter un tag");
        addTagButton->setStyleSheet("margin : 20; border: none; text-decoration: underline;");
        connect(addTagButton,SIGNAL(clicked()),this,SLOT(on_addTag_clicked()));
        tags->layout()->addWidget(addTagButton);
        ui->tagScrollArea->setWidget(tags);
    }
    else {
        ui->infoMenu->hide();
        ui->current_picture->setPixmap(originalPixmap);
    }
}

//void viewer::on_tag_editingFinished(int i) {
//    Image thisImage = liste_image[static_cast<unsigned int>(position)];
//    bibliotheque->deleteTag(thisImage.getTags()[i]);
//    cout << "Suppression du tag " + thisImage.getTags()[i] << endl;
//    bibliotheque->addTag(thisImage.getChemin(), tag[i]->text().toStdString());
//    cout << "Ajout du tag " + tag[i]->text().toStdString() << endl;
//}

void viewer::on_addTag_clicked(){
    addTagButton->hide();

    //Setup the combobox
    QComboBox *otherTags = new QComboBox();
    tags->layout()->removeWidget(addTagButton);
    tags->layout()->removeWidget(otherTags);
    otherTags->addItem("Autres tags...");
    QStandardItemModel* model =
            qobject_cast<QStandardItemModel*>(otherTags->model());
    QModelIndex firstIndex = model->index(0, otherTags->modelColumn(),
            otherTags->rootModelIndex());
    QStandardItem* firstItem = model->itemFromIndex(firstIndex);
    firstItem->setSelectable(false);

    //Add remaining existing tags to the combobox
    Image thisImage = liste_image[static_cast<unsigned int>(position)];
    vector<string> imgtags = thisImage.getTags();
    for (unsigned int i = 0; i < bibliotheque->getAllTags().size(); i++) {
        string tag = bibliotheque->getAllTags()[i];
        if (std::find(imgtags.begin(), imgtags.end(), tag) == imgtags.end()) {
            //if the current image does not contain this tag
            otherTags->addItem(QString::fromStdString(tag));
        }
    }

    //Possibility to add a non-existing tag
    otherTags->addItem(QString::fromStdString("Nouveau tag..."));
    tags->layout()->addWidget(otherTags);
    connect(otherTags,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_comboBox_currentIndexChanged(const QString)));

}

void viewer::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1.compare("Nouveau tag...") != 0) { // if existing tag is clicked
        bibliotheque->addTag(liste_image[static_cast<unsigned int>(position)].getChemin(), arg1.toStdString());
        this->liste_image = bibliotheque->getlisteImage();
        bibliotheque->addTag(this->liste_image[static_cast<unsigned int>(position)].getId(), arg1.toStdString());
        this->liste_image[static_cast<unsigned int>(position)].addTag(arg1.toStdString());
        ui->infoMenu->hide(); //updateInfoBar();// ne marche pas
    }
    else { // creates dialog to enter new non-empty tag
        AjoutTagDialog *atd = new AjoutTagDialog;
        atd->exec();
        QString newTag = atd->getValue();
        if(newTag.compare("") != 0) {
            bibliotheque->addTag(liste_image[static_cast<unsigned int>(position)].getChemin(), newTag.toStdString());
            bibliotheque->addTag(this->liste_image[static_cast<unsigned int>(position)].getId(), newTag.toStdString());
            this->liste_image[static_cast<unsigned int>(position)].addTag(newTag.toStdString());
            ui->infoMenu->hide();
            tags->layout()->addWidget(addTagButton);
        }
    }
    bibliothequeWidget->refreshView();
    bibliotheque->updateCSV();
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


void viewer::on_quitButton_clicked()
{
    on_info_clicked();
}



/*****************************************************************************************
 *                               NEXT/PREVIOUS                                           *
 *****************************************************************************************/
void viewer::on_next_picture_clicked()
{
    this->rotate = 90;
    if(position < static_cast<int>(this->liste_image.size() - 1)){
    position ++;

    }
    else {
        position = 0;
    }

    QPixmap pixmap = QPixmap::fromImage(*liste_image[static_cast<unsigned int>(position)].getQImage());
    ui->current_picture->setPixmap(pixmap);
    updateInfoBar();
    QMainWindow::setWindowTitle(QString::fromStdString(this->liste_image[static_cast<unsigned int>(this->position)].getChemin()));
}

void viewer::on_previous_picture_clicked()
{
    this->rotate = 90;
    if(position > 0){
     position --;
    }
    else {
        position = static_cast<int>(this->liste_image.size() - 1);
    }

    QPixmap pixmap = QPixmap::fromImage(*liste_image[static_cast<unsigned int>(position)].getQImage());
    ui->current_picture->resize(pixmap.size());
    ui->current_picture->setPixmap(pixmap);

    updateInfoBar();
    QMainWindow::setWindowTitle(QString::fromStdString(this->liste_image[static_cast<unsigned int>(this->position)].getChemin()));
}

/*****************************************************************************************
 *                                     DELETE                                            *
 *****************************************************************************************/
void viewer::deleteImage()
{
    bibliotheque->removeImage(this->liste_image[static_cast<unsigned int>(this->position)].getId());
    liste_image.erase(liste_image.begin() + position);

    if(position == static_cast<int>(liste_image.size())) {
        position--;
    }
    QPixmap pixmap = QPixmap::fromImage(*liste_image[static_cast<unsigned int>(position)].getQImage());
    ui->current_picture->resize(pixmap.size());
    ui->current_picture->setPixmap(pixmap);

    this->bibliothequeWidget->refreshView();

}

void viewer::on_deleteButton_clicked()
{
    confirmDelete *cd = new confirmDelete();
    cd->exec();
    if(cd->getValue() == true)
        deleteImage();
    delete cd;
}

void viewer::on_favourite_pressed()
{
    Image thisImage = bibliotheque->getlisteImage()[static_cast<unsigned long>(this->position)];
    if (thisImage.getFav() == 0) {
        thisImage.setFav();
        bibliotheque->setFav(thisImage.getId());
        QPixmap pixmap6("../BibliothequePhoto/icons/star-filled.svg");
        QIcon ButtonIcon6(pixmap6);
        ui->favourite->setIcon(ButtonIcon6);
        cout << "Ajoutée aux favoris" << endl;
    }
    else {
        thisImage.delFav();
        bibliotheque->delFav(thisImage.getId());
        QPixmap pixmap7("../BibliothequePhoto/icons/star.svg");
        QIcon ButtonIcon7(pixmap7);
        ui->favourite->setIcon(ButtonIcon7);
        cout << "supprimée des favoris" << endl;
    }
}
