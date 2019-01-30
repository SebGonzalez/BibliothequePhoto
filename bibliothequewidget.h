#ifndef BIBLIOTHEQUEWIDGET_H
#define BIBLIOTHEQUEWIDGET_H

#include "bibliotheque.h"
#include <QListWidget>

class BibliothequeWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit BibliothequeWidget(int pieceSize, QWidget *parent = nullptr, Bibliotheque *bibliotheque = nullptr);
    void addPiece(const QPixmap &pixmap, int i);

    static QString bibliothequeMimeType() { return QStringLiteral("image/icon-photo"); }

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;
//    void mousePressEvent(QMouseEvent *event);

    int m_PieceSize;
    Bibliotheque *m_bibliotheque;

};
#endif // BIBLIOTHEQUEWIDGET_H
