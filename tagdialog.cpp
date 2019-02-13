#include "tagdialog.h"
#include "ui_tagdialog.h"
#include "QPushButton"
tagDialog::tagDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tagDialog)
{
    ui->setupUi(this);
}

tagDialog::~tagDialog()
{
    delete ui;
}

tagDialog::tagDialog(Bibliotheque bibliotheque):
    ui(new Ui::tagDialog)
{
    ui->setupUi(this);
    biblio_ = bibliotheque;
    init();

 }

void tagDialog::on_click_button(){

    QObject* button = QObject::sender();
    QString clicked_tag = button->objectName();
    chosen_tag = clicked_tag;
    this->close();

}

void tagDialog::init(){

    ui->vertLayout->setMargin(45);
    tags = biblio_.getAllTags();
    for(int i = 0 ; i < tags.size() ; i ++){
        QPushButton *button = new QPushButton(tags[i].c_str());
        button->setObjectName(tags[i].c_str());
        connect(button, SIGNAL(clicked()), this, SLOT(on_click_button()));
        ui->vertLayout->addWidget(button);

   }
}

