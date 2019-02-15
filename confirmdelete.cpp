#include "confirmdelete.h"
#include "ui_confirmdelete.h"

confirmDelete::confirmDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmDelete)
{
    ui->setupUi(this);
    confirm = false;
}

confirmDelete::~confirmDelete()
{
    delete ui;
}

void confirmDelete::on_buttonBox_accepted()
{
    confirm = true;
    ui->~confirmDelete();
}

void confirmDelete::on_buttonBox_rejected()
{
    confirm = false;
    ui->~confirmDelete();
}

bool confirmDelete::getValue() {
    return confirm;
}
