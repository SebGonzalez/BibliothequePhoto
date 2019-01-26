#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHoverEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:

    QString current_image;
    QList <QString> liste_image;

    explicit Dialog(QWidget *parent = nullptr);

    Dialog(QString current_image,QList <QString> listeImage){
        this->current_image = current_image;
        this->liste_image = listeImage;
    }
    ~Dialog();


    void initLabels();
    void loadImagesfromList();

public slots:


    void nextImage();
    void previousImage();



private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
