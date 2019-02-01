#include "ajouttag.h"
#include "ui_ajouttag.h"

AjoutTag::AjoutTag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutTag)
{
    this->setFixedSize(380, 100);
    ui->setupUi(this);

    //Backgound image
}

AjoutTag::~AjoutTag()
{
    delete ui;
}

void AjoutTag::on_buttonBox_accepted()
{
    tagName.assign(ui->lineEdit->text().toStdString());
}

void AjoutTag::on_buttonBox_rejected()
{
    close();
}
