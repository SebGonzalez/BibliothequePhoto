#ifndef BIBLIOTHEQUEWIDGET_H
#define BIBLIOTHEQUEWIDGET_H

#include "bibliotheque.h"
#include "ajouttag.h"
#include "textoverphoto.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QTimer>
#include <QMenu>
#include <QListWidget>
#include <QPainter>
#include <QCursor>
#include <QSignalMapper>



class BibliothequeWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit BibliothequeWidget(int pieceSize, QWidget *parent = nullptr, Bibliotheque *bibliotheque = nullptr);

    void refreshView();
    void refreshFavView();
    void addPiece(const QPixmap &pixmap, int i,std::string textTag);
    static QString bibliothequeMimeType() { return QStringLiteral("image/icon-photo"); }


private slots:
    void ShowContextMenu(const QPoint& pos);
    //void mouseMoveEvent(QMouseEvent *event) override;
    void displayLabel2(QListWidgetItem* item);
    void displayLabel();
    void hideLabel();
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;
    float time;
    int m_PieceSize;
    int previousIdPhoto;
    Bibliotheque *m_bibliotheque;
    QTimer *timer = new QTimer(this);
    QCursor *cursor = new QCursor();
    QListWidgetItem* itemHovered;
     QListWidgetItem* previousItemHovered;
    QLabel *infos = new QLabel(this);
};
#endif // BIBLIOTHEQUEWIDGET_H
