#include "tagdialog.h"
#include "ui_tagdialog.h"
#include "QPushButton"
#include <QCommonStyle>
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

void tagDialog::on_clickButton(){

    QObject* button = QObject::sender();
    QString clicked_tag = button->objectName();
    chosen_tag = clicked_tag;
    this->close();

}

void tagDialog::on_DeleteButton(){
    QObject* button = QObject::sender();
    QString deleted_tag = button->objectName();
    chosenDeletedtag = deleted_tag;
    //this->close();
}

void tagDialog::init(){

    tags = biblio_.getAllTags();
    for(int i = 0 ; i < tags.size() ; i ++){
        QPushButton *button = new QPushButton(tags[i].c_str());
        QPushButton *button2 = new QPushButton("Supprimer le tag");

        button->setObjectName(tags[i].c_str());
        button2->setObjectName(tags[i].c_str());

        graphicsEffects(button);

        connect(button, SIGNAL(clicked()), this, SLOT(on_clickButton()));
        connect(button2, SIGNAL(clicked()), this, SLOT(on_DeleteButton()));


        ui->gridLayout->addWidget(button,i,0);
        ui->gridLayout->addWidget(button2,i,1);



   }
}

void tagDialog::graphicsEffects(QPushButton *button){
    button->setStyleSheet("border: 1px solid black; background: white;");
    button->setStyleSheet(" QPushButton:hover{background: grey;}");
    button->resize(150,20);
    button->setMinimumSize(150,20);
}



