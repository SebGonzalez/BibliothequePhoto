#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include "bibliotheque.h"

namespace Ui {
class viewer;
}

class viewer : public QMainWindow
{
    Q_OBJECT

public:
    std::vector<Image> liste_image;
    int position;
    int rotate;

    explicit viewer(QWidget *parent = nullptr);
    viewer(int position, Bibliotheque &bibliotheque, std::vector<Image> listeImage);
    ~viewer();

private slots:
    void on_zoom_clicked();

    void on_zoomOut_clicked();

    void on_rotate_clicked();

    void on_info_clicked();

private:
    Ui::viewer *ui;

    Bibliotheque *bibliotheque;
};

#endif // VIEWER_H
