#include "bibliothequewidget.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

BibliothequeWidget::BibliothequeWidget(int pieceSize, QWidget *parent, Bibliotheque *bibliotheque)
    : QListWidget(parent), m_PieceSize(pieceSize)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(m_PieceSize, m_PieceSize));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    m_bibliotheque = bibliotheque;
}

void BibliothequeWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(BibliothequeWidget::bibliothequeMimeType()))
        event->accept();
    else
        event->ignore();
}

void BibliothequeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(BibliothequeWidget::bibliothequeMimeType())) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void BibliothequeWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat(BibliothequeWidget::bibliothequeMimeType())) {
        QByteArray pieceData = event->mimeData()->data(BibliothequeWidget::bibliothequeMimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;

        int ligne = event->pos().y()/200;
        int colonne = (event->pos().x())/200;
        QListWidgetItem *pieceItem = new QListWidgetItem();
        pieceItem->setIcon(QIcon(pixmap));
         pieceItem->setData(Qt::UserRole, QVariant(pixmap));
        pieceItem->setData(Qt::UserRole+1, QVariant(0));

        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);


        int rowPhoto = ligne*6 + colonne;
        std::cout << ligne <<" OOOOOOOOO " << colonne << " AAAAAA " << rowPhoto << std::endl;

        takeItem(row(currentItem()));
        insertItem(rowPhoto, pieceItem);
        setCurrentRow(rowPhoto);
       // addPiece(pixmap, 0);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void BibliothequeWidget::addPiece(const QPixmap &pixmap, int i)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
     pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, QVariant(i));

    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

void BibliothequeWidget::startDrag(Qt::DropActions)
{
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();

    dataStream << pixmap << location;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(BibliothequeWidget::bibliothequeMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    drag->exec(Qt::MoveAction);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
       delete takeItem(row(item));
}
