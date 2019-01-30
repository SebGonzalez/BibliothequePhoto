#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent) :
    QLabel(parent)
{

}

ClickableLabel::ClickableLabel(int indice){
    this->indice = indice;
}

void  ClickableLabel::mousePressEvent(QMouseEvent *ev){
    emit clicked();
}

