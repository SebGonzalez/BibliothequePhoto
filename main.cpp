#include "mainwindow.h"
#include <QApplication>
//#include "bibliotheque.h"

#include "mainwindowredesigned.h"
#include "viewer.h"
#include "landingpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//   MainWindow w;
//    w.show();
    LandingPage *lp = new LandingPage();
    lp->exec();
    MainWindowRedesigned m;
    m.show();

    return a.exec();
}
