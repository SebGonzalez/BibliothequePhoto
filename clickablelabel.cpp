#include "clickablelabel.h"

using namespace std;

ClickableLabel::ClickableLabel(QWidget *parent) :
    QLabel(parent)
{

}

ClickableLabel::ClickableLabel(int indice){
    this->indice = indice;
}

void  ClickableLabel::mousePressEvent(QMouseEvent *ev){
    cout << "test" << endl;

    emit clicked();
}

