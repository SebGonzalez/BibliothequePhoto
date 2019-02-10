#include "mainwindowredesigned.h"
#include "ui_mainwindowredesigned.h"
#include "bibliotheque.h"
#include "dialog.h"
#include "landingpage.h"
#include "image.h"
#include "viewer.h"

#include <QPixmap>
#include <iostream>
#include <qdebug.h>
#include <QGuiApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QGridLayout>

using namespace std;

MainWindowRedesigned::MainWindowRedesigned(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRedesigned)
{
    ui->setupUi(this);

    vector<Image> selection;
    selection = bibliotheque.getlisteImage();
    frameLayout = new QGridLayout(ui->selection);
    int scale = 200;
    bibliothequeWigdet = new BibliothequeWidget(scale,this, &bibliotheque);
    for(unsigned int i = 0; i < selection.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*selection[i].getQImage());
        //pixmap = pixmap.scaledToWidth(400);
        //pixmap.scaledToHeight(200);
        pixmap = pixmap.scaled(scale, scale);

        bibliothequeWigdet->addPiece(pixmap, selection[i].getId());
    }
    bibliothequeWigdet->setStyleSheet("background-color: pink");
    frameLayout->addWidget(ui->widget);
    frameLayout->addWidget(bibliothequeWigdet);

}

MainWindowRedesigned::~MainWindowRedesigned()
{
    delete ui;
}

void MainWindowRedesigned::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   cout << "ya tebradi" << endl;

   frameLayout->removeWidget(bibliothequeWigdet);
   bibliothequeWigdet->resize(ui->selection->frameSize().width(), ui->selection->frameSize().height());
   bibliothequeWigdet->update();

   frameLayout->addWidget(bibliothequeWigdet);
   //frameLayout->update();
}
