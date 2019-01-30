#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bibliotheque.h"
#include "dialog.h"
#include "landingpage.h"

#include <QPixmap>
#include <iostream>
#include <qdebug.h>

using namespace std;

    Bibliotheque bibliotheque;
    vector<Image> selection;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //Landing page : Commenter les 3 prochaines lignes pour avoir la galerie
    LandingPage *lp = new LandingPage(this);
    lp->exec();

    this->setFixedSize(1600,900);
    ui->setupUi(this);


    //Main gallery
    selection = bibliotheque.getlisteImage();

    displayPic("PicsTmp/Younes.png");
    getFics("PicsTmp/");
    showTreeView();


    QHBoxLayout *frameLayout = new QHBoxLayout(ui->frame);
    bibliothequeWigdet = new BibliothequeWidget(200,this, &bibliotheque);
    for(unsigned int i = 0; i < selection.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*selection[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
          bibliothequeWigdet->addPiece(pixmap.scaled(200,200), i);
    }
   frameLayout->addWidget(bibliothequeWigdet);

   QObject::connect(bibliothequeWigdet, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(displayDialogue(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    //Reset file and save all updated data before closing
    bibliotheque.initDataFile();
    for (int i = 0; i < bibliotheque.getImgListSize(); i++) {
        bibliotheque.addToFile(bibliotheque.getlisteImage()[i]);
    }
    delete ui;
}

void MainWindow::displayPic(string path)
{
    QPixmap pix;
    pix.load(path.c_str());
    ui->label->setPixmap(pix.scaled(ui->label->width(),ui->label->height()));

}

void MainWindow::getFics(string path)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
          string str(ent->d_name);
          if(str.find('png') != string::npos)
            printf ("%s\n", ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("Can't Open");
    }
}

void MainWindow::showTreeView()
{
    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());
    ui->treeView->setModel(model);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
}

void MainWindow::on_pushButton_clicked()
{
    if(textChange == true){
        tag = new QPushButton(this);
        tag->setText(ui->lineEdit->text());
        ui->formLayout->addWidget(tag);
        selection = bibliotheque.getTaggedImages(ui->lineEdit->text().toStdString());

        //Debug
        for(int i = 0; i < selection.size(); i++) {
            cout << selection[i].getChemin() << endl;
        }
        //


        QHBoxLayout *frameLayout = new QHBoxLayout(ui->frame);
        bibliothequeWigdet->clear();
        bibliothequeWigdet = new BibliothequeWidget(200,this, &bibliotheque);
        for(unsigned int i = 0; i < selection.size(); i++) {
            QPixmap pixmap = QPixmap::fromImage(*selection[i].getQImage());
            pixmap = pixmap.scaledToWidth(200);
            //pixmap.scaledToHeight(200);
              bibliothequeWigdet->addPiece(pixmap.scaled(200,200), i);
        }
       frameLayout->addWidget(bibliothequeWigdet);

        //connect(tag, SIGNAL (released()), this, SLOT (handleButton()));
        //qDebug() << __FUNCTION__ << "Button created";
    }
}


void MainWindow::handleButton()
{
    tag->setText("Example");
    tag->resize(100,100);
   // qDebug() << __FUNCTION__ << "Slot";
}

void MainWindow::on_lineEdit_textChanged()
{
    textChange =true;
}


void MainWindow::displayDialogue(QListWidgetItem *item)
{

     Dialog *dialog = new Dialog(item->data(Qt::UserRole+1).toInt() ,bibliotheque.getlisteImage());
     dialog->exec();


}
