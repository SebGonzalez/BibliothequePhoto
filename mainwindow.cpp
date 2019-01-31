#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bibliotheque.h"
#include "dialog.h"
#include "landingpage.h"

#include <QPixmap>
#include <iostream>
#include <qdebug.h>
#include <QGuiApplication>
#include <QRect>
#include <QDesktopWidget>

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

    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();

    this->setFixedSize(width,height);

    ui->setupUi(this);


    //Main gallery
    selection = bibliotheque.getlisteImage();

    showTreeView();

    QHBoxLayout *frameLayout = new QHBoxLayout(ui->frame);
    bibliothequeWigdet = new BibliothequeWidget(200,this, &bibliotheque);
    for(unsigned int i = 0; i < selection.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*selection[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);

        bibliothequeWigdet->addPiece(pixmap.scaled(200,200), selection[i].getId());
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

void MainWindow::on_treeView_expanded(const QModelIndex &index)
{
    QFileSystemModel model;
    qDebug() << model.filePath(index) << endl;
    bibliotheque.addDirectoryArb(ui->frame, model.filePath(index).toStdString());

    selection = bibliotheque.getlisteImage();
    bibliothequeWigdet->clear();
    for(unsigned int i = 0; i < selection.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*selection[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
        bibliothequeWigdet->addPiece(pixmap, i);
    }
}
