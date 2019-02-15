
#include <QApplication>
//#include "bibliotheque.h"

#include "mainwindowredesigned.h"
#include "viewer.h"
#include "landingpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindowRedesigned m;
    if(m.getEmptyBibliotheque() == true){
        LandingPage *lp = new LandingPage();
        lp->exec();

    }
    m.show();

    return a.exec();
}
