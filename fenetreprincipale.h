#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include "bibliotheque.h"
#include "dialog.h"
#include "landingpage.h"
#include "bibliothequewidget.h"


namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    Bibliotheque bibliotheque;
    vector<Image> selection;

    explicit FenetrePrincipale(QWidget *parent = nullptr);
    ~FenetrePrincipale();

private:
    BibliothequeWidget *bibliothequeWigdet;
    Ui::FenetrePrincipale *ui;
};

#endif // FENETREPRINCIPALE_H
