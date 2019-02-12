#ifndef BIBLIOTHEQUEWIDGET_H
#define BIBLIOTHEQUEWIDGET_H

#include "bibliotheque.h"
#include "ajouttag.h"
#include <QListWidget>
#include <QPainter>

class BibliothequeWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit BibliothequeWidget(int pieceSize, QWidget *parent = nullptr, Bibliotheque *bibliotheque = nullptr);

    void refreshView();
    void addPiece(const QPixmap &pixmap, int i,std::string textTag);
    static QString bibliothequeMimeType() { return QStringLiteral("image/icon-photo"); }


private slots:
    void ShowContextMenu(const QPoint& pos);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;

    int m_PieceSize;
    Bibliotheque *m_bibliotheque;
};
#endif // BIBLIOTHEQUEWIDGET_H
