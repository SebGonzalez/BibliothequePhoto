#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class ClickableLabel : public QLabel
{
    Q_OBJECT
    bool is_clicked = false;
public:
    ClickableLabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e);

signals:
    void clicked();

public slots:
};

#endif // CLICKABLELABEL_H
