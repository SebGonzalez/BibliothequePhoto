#include "mainwindowredesigned.h"
#include "ui_mainwindowredesigned.h"

MainWindowRedesigned::MainWindowRedesigned(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRedesigned)
{
    ui->setupUi(this);
}

MainWindowRedesigned::~MainWindowRedesigned()
{
    delete ui;
}
