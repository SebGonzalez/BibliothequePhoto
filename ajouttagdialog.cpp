#include "ajouttagdialog.h"
#include "ui_ajouttagdialog.h"

AjoutTagDialog::AjoutTagDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutTagDialog)
{
    ui->setupUi(this);
    value = "";
}

AjoutTagDialog::~AjoutTagDialog()
{
    delete ui;
}

void AjoutTagDialog::on_buttonBox_accepted()
{
    value = ui->lineEdit->text();
}

void AjoutTagDialog::on_buttonBox_rejected()
{
    value = "";
    ui->~AjoutTagDialog();
}

QString AjoutTagDialog::getValue() {
    return value;
}
