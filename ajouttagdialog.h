#ifndef AJOUTTAGDIALOG_H
#define AJOUTTAGDIALOG_H

#include <QDialog>

namespace Ui {
class AjoutTagDialog;
}

class AjoutTagDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutTagDialog(QWidget *parent = nullptr);
    ~AjoutTagDialog();
    QString getValue();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AjoutTagDialog *ui;
    QString value;
};

#endif // AJOUTTAGDIALOG_H
