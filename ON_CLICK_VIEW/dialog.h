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
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void initLabels();
    void loadImagesfromList();



signals:
    void Mouse_moving();

public slots:


    void nextImage();
    void previousImage();
    void mouseMoving();



private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
