
#include <QApplication>
//#include "bibliotheque.h"

#include "mainwindowredesigned.h"
#include "viewer.h"
#include "landingpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindowRedesigned m;
    m.show();

    return a.exec();
}
