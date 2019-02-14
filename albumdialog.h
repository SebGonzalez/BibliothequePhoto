#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

#include <QDialog>
#include "bibliothequewidget.h"

namespace Ui {
class AlbumDialog;
}

class AlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumDialog(QWidget *parent = nullptr);
    AlbumDialog(Bibliotheque &bibliotheque, BibliothequeWidget &bibliothequeWidget);
    ~AlbumDialog();

private:
    Ui::AlbumDialog *ui;
    Bibliotheque *bibliotheque;
    BibliothequeWidget *bibliothequeWidget;
};

#endif // ALBUMDIALOG_H
