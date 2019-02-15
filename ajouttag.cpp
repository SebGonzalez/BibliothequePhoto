#include "ajouttag.h"
#include "ui_ajouttag.h"

AjoutTag::AjoutTag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutTag)
{
    ui->setupUi(this);
}

AjoutTag::~AjoutTag()
{
    delete ui;
}

void AjoutTag::on_buttonBox_accepted()
{
    if(asBeenChanged)
        tagName.assign(ui->lineEdit->text().toStdString());
}

void AjoutTag::on_buttonBox_rejected()
{
    close();
}

void AjoutTag::on_lineEdit_textChanged(const QString &arg1)
{
    arg1.size();
    asBeenChanged = true;
}
