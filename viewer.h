#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include "bibliothequewidget.h"

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
    QSize originalSize ;
    explicit viewer(QWidget *parent = nullptr);
    viewer(int position, Bibliotheque &bibliotheque, BibliothequeWidget &bibliothequeWidget);
    ~viewer();

private slots:
    void on_zoom_clicked();

    void on_zoomOut_clicked();

    void on_rotate_clicked();

    void on_info_clicked();

    void on_next_picture_clicked();

    void on_previous_picture_clicked();

    void on_quitButton_clicked();

    void on_addTag_clicked();

    void on_tag_editingFinished(int i);

    void on_filename_editingFinished();

    void on_deleteButton_clicked();

private:
    Ui::viewer *ui;

    Bibliotheque *bibliotheque;
    BibliothequeWidget *bibliothequeWidget;
    void updateInfoBar();
    void deleteImage();

};

#endif // VIEWER_H
