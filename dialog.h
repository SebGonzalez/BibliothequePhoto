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
    int rotate;
    std::vector<Image> liste_image;

    explicit Dialog(QWidget *parent = nullptr);
    Dialog(int position, Bibliotheque &bibliotheque, std::vector<Image> listeImage);
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
    void modifierTags();
    void validateModifications();




private slots:
    void on_buttonThrow_pressed();

private:
    Ui::Dialog *ui;
    Bibliotheque *bibliotheque;
};

#endif // DIALOG_H
