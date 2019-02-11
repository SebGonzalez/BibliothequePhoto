#include "mainwindow.h"
#include <QApplication>
//#include "bibliotheque.h"

#include "mainwindowredesigned.h"
#include "viewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  MainWindow w;
   // w.show();

    MainWindowRedesigned m;
    m.show();

    return a.exec();
}
