#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHoverEvent>
#include <bibliotheque.h>
#include <image.h>
#include <QPlainTextEdit>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:

    int position;
    std::vector<Image> liste_image;
    int rotate;

    explicit Dialog(QWidget *parent = nullptr);
    Dialog(int position,std::vector<Image> listeImage);
    ~Dialog();


    void initLabels();
    void loadImagesfromList();
    QPixmap resizePixmap(QLabel *label, QPixmap pixmap);
    QPlainTextEdit* labelVisualSettings(QPlainTextEdit *label);


public slots:


    void nextImage();
    void previousImage();
    void displayTags();
    void rotatePicture();



private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
