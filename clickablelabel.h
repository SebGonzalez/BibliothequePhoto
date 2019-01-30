#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <stdio.h>

class ClickableLabel : public QLabel
{
    Q_OBJECT
    bool is_clicked = false;
    int indice;
public:
    ClickableLabel(QWidget *parent = 0);
    ClickableLabel(int indice);
    void mousePressEvent(QMouseEvent *e);

signals:
    void clicked();

public slots:
};

#endif // CLICKABLELABEL_H
