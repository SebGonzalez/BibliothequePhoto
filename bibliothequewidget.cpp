
#include "bibliothequewidget.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMenu>

BibliothequeWidget::BibliothequeWidget(int pieceSize, QWidget *parent, Bibliotheque *bibliotheque)
    : QListWidget(parent), m_PieceSize(pieceSize)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(m_PieceSize, m_PieceSize));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setUniformItemSizes(true);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowContextMenu(const QPoint&)));

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

        int ligne = event->pos().y()/210;
        int colonne = (event->pos().x())/210;
        int idPhoto = currentItem()->data(Qt::UserRole+1).toInt();
        QListWidgetItem *pieceItem = new QListWidgetItem();
        pieceItem->setIcon(QIcon(pixmap.scaled(200,200)));
         pieceItem->setData(Qt::UserRole, QVariant(pixmap));
        pieceItem->setData(Qt::UserRole+1, QVariant(idPhoto));

        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);


        int rowPhoto = ligne*5 + colonne+1;
           if(row(currentItem()) >= rowPhoto) {
               rowPhoto--;
           }
        m_bibliotheque->updatePositionPhoto(idPhoto, rowPhoto);

        std::cout << ligne <<" OOOOOOOOO " << colonne << " AAAAAA " << rowPhoto << std::endl;


        insertItem(rowPhoto, pieceItem);
        setCurrentRow(rowPhoto);
       // addPiece(pixmap, 0);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void BibliothequeWidget::addPiece(const QPixmap &pixmap, int id)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
     pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, QVariant(id));
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

void BibliothequeWidget::ShowContextMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos = QCursor::pos();
    Bibliotheque biblio;
    vector<string> listeTags = biblio.getAllTags();

    QMenu *myMenu = new QMenu();
    QMenu* addTag = myMenu->addMenu( "Ajouter un tag..." );
    QAction* tagsMenu;
    for (int i = 0; i < listeTags.size(); ++i) {
        tagsMenu = addTag->addAction( QString::fromStdString(listeTags[i]));
    }


//    myMenu.addMenu()
//    myMenu.addAction("Supprimer");

    QAction* selectedItem = myMenu->exec(globalPos);
    if (selectedItem)
    {
        // something was chosen, do stuff
    }
    else
    {
        // nothing was chosen
    }
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

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
       delete takeItem(row(item));
}
