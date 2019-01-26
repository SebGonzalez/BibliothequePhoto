#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent) :
    QLabel(parent)
{

}

void  ClickableLabel::mousePressEvent(QMouseEvent *ev){
    this->is_clicked = true;
    emit clicked();
}
