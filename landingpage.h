#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include <QDialog>
#include <bibliotheque.h>
namespace Ui {
class LandingPage;
}

class LandingPage : public QDialog
{
    Q_OBJECT

public:
    explicit LandingPage(QWidget *parent = nullptr);
     Bibliotheque *bibliotheque;
    ~LandingPage();
     LandingPage(Bibliotheque *bibliotheque);

public slots:

    void displayMainWindow();



private slots:
    void on_importer_clicked();

private:
    Ui::LandingPage *ui;





};

#endif // LANDINGPAGE_H
