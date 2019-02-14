    #include "bibliothequewidget.h"

BibliothequeWidget::BibliothequeWidget(int pieceSize, QWidget *parent, Bibliotheque *bibliotheque)
    : QListWidget(parent), m_PieceSize(pieceSize)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(m_PieceSize, m_PieceSize));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setResizeMode(QListView::Adjust);
    setUniformItemSizes(true);
    setMouseTracking(true);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    TextOverPhoto *textOver = new TextOverPhoto(this);
    setItemDelegate(textOver);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowContextMenu(const QPoint&)));

    connect(timer, SIGNAL(timeout()), this, SLOT(displayLabel()));
    //    connect(this, SIGNAL(itemEntered(QListWidgetItem* )), this, SLOT(displayLabel(QListWidgetItem* )));
    timer->start(1500);

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

        this->width();
        cout << "Width : " << this->width() << endl;
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
        pieceItem->setData(Qt::UserRole+2, currentItem()->data(Qt::UserRole+2));
        pieceItem->setData(Qt::UserRole+3, currentItem()->data(Qt::UserRole+3));

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

void BibliothequeWidget::addPiece(const QPixmap &pixmap, int id, string textTag)
{
    QListWidgetItem *pieceItem = new QListWidgetItem( this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, QVariant(id));
    pieceItem->setData(Qt::UserRole+2, QString::fromStdString(textTag));
    pieceItem->setData(Qt::UserRole+3, QString::fromStdString(textTag));
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

}

void BibliothequeWidget::refreshView()
{
    this->clear();
    vector<Image> Img = m_bibliotheque->getlisteImage();

    for(unsigned int i = 0; i < m_bibliotheque->getlisteImage().size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*Img[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
        this->addPiece(pixmap.scaled(200,200), m_bibliotheque->getlisteImage()[i].getId(),m_bibliotheque->getlisteImage()[i].getTagsString());
    }
}

void BibliothequeWidget::ShowContextMenu(const QPoint& pos) // this is a slot
{
    infos->clear();
    infos->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
    infos->setStyleSheet("QLabel { background-color : none;}");

    QPoint globalPos = QCursor::pos();
    vector<string> listeTags = m_bibliotheque->getAllTags();
    vector<string> listeAlbums = m_bibliotheque->getAllAlbums();
    vector<Image> listeImage = m_bibliotheque->getlisteImage();

    QMenu *myMenu = new QMenu();

    QMenu* addTag = myMenu->addMenu( "Ajouter un tag..." );
    QMenu* deleteTag = myMenu->addMenu( "Supprimer un tag..." );
    QMenu* addAlbum = myMenu->addMenu( "Ajouter à un album..." );
    myMenu->addAction( "Supprimer" );
    QAction* supprimerAlbum = myMenu->addAction( "Supprimer de l'album" );

    QAction* tagsMenu;
    for (unsigned int i = 0; i < listeTags.size(); ++i) {
        tagsMenu = addTag->addAction( QString::fromStdString(listeTags[i]));
        tagsMenu = deleteTag->addAction( QString::fromStdString(listeTags[i]));
    }
    tagsMenu = addTag->addAction("Nouveau tag ...");

    QAction* albumsMenu;
    for (unsigned int i = 0; i < listeAlbums.size(); ++i) {
        albumsMenu = addAlbum->addAction( QString::fromStdString(listeAlbums[i]));
    }
    albumsMenu = addAlbum->addAction("Nouvel album ...");

    QList<QListWidgetItem*> listeItems = selectedItems();
    QAction* selectedTag = myMenu->exec(globalPos);

    if (selectedTag)
    {
        if(!QString::compare(selectedTag->iconText(),"Supprimer")){
            for (int i = 0; i < listeItems.size(); ++i) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                m_bibliotheque->removeImage(idPhoto);
            }

            m_bibliotheque->updateCSV();

        }
        else if(!QString::compare(selectedTag->iconText(),"Nouveau tag")){
            AjoutTag *ajout = new AjoutTag(this);
            ajout->exec();
            if(ajout->result() != 0){
                string addedTag = ajout->tagName;
                if(addedTag.size() != 0){
                    for (int i = 0; i < listeItems.size(); i++) {
                        int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();

                        m_bibliotheque->addTag(idPhoto,addedTag);

                        QString text = listeItems[i]->data(Qt::UserRole+3).toString() + ", " + QString::fromStdString(addedTag);
                        if(listeItems[i]->data(Qt::UserRole+2).toString() != "")
                            listeItems[i]->setData(Qt::UserRole+2, text);
                        listeItems[i]->setData(Qt::UserRole+3, text);

                    }
                    cout << addedTag << endl;
                }
            }
        }
        else if(selectedTag == albumsMenu) {
            cout << "Nouvel album" << endl;
            AjoutTag *ajout = new AjoutTag(this);
            ajout->exec();
            if(ajout->result() != 0){
                string addedAlbum = ajout->tagName;
                if(addedAlbum.size() != 0){
                    for (int i = 0; i < listeItems.size(); i++) {
                        int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();

                        m_bibliotheque->getImageById(idPhoto)->setAlbum(addedAlbum);
                    }
                }
            }
        }
        else if(selectedTag == supprimerAlbum) {

            for (int i = 0; i < listeItems.size(); i++) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();

                m_bibliotheque->getImageById(idPhoto)->setAlbum("NULL");
            }

        }
        else if(m_bibliotheque->isAlbum(selectedTag->iconText().toStdString())) {
            cout << "OOOOOOOOOO" << endl;
            for (int i = 0; i < listeItems.size(); i++) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                string selectedAlbumToString = selectedTag->iconText().toStdString();
                m_bibliotheque->getImageById(idPhoto)->setAlbum(selectedAlbumToString);
            }
        }else {

            string selectedTagToString = selectedTag->iconText().toStdString();
            for (int i = 0; i < listeItems.size(); ++i) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                m_bibliotheque->addTag(idPhoto,selectedTagToString);
                QString text = listeItems[i]->data(Qt::UserRole+3).toString() + ", " + QString::fromStdString(selectedTagToString);
                if(listeItems[i]->data(Qt::UserRole+2).toString() != "")
                    listeItems[i]->setData(Qt::UserRole+2, text);
                listeItems[i]->setData(Qt::UserRole+3, text);
            }
        }
        refreshView();

    }
}


void BibliothequeWidget::displayLabel()
{
    QPoint globalPos = this->mapFromGlobal(QCursor::pos());
    infos->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    infos->setStyleSheet("QLabel { background-color : white; color : black; }");

    infos->setGeometry(globalPos.x(),globalPos.y(),500,100);
    if(infos->text().size() != 0)
        infos->show();
    else
        infos->hide();
    connect(this, SIGNAL(itemEntered(QListWidgetItem* )), this, SLOT(displayLabel2(QListWidgetItem* )));
}

void BibliothequeWidget::displayLabel2(QListWidgetItem* item)
{
    infos->hide();
    timer->start(800);
    int idPhoto = item->data(Qt::UserRole+1).toInt();
    if(idPhoto != previousIdPhoto){
        QString infosImages ;
        Image *Img = m_bibliotheque->getImageById(idPhoto);
        QString chemin = QString::fromStdString( Img->getChemin());
        QString album = QString::fromStdString( Img->getAlbum());
        float size = m_bibliotheque->GetFileSize(*Img)/1000;
        QSize dimension = m_bibliotheque->getDimension(*Img);
        QString dimensionW = QString::number(dimension.width());
        QString dimensionH = QString::number(dimension.height());
        vector <string> tags = Img->getTags();
        QString stringTags = "Tags : ";
        for (int i = 0; i < tags.size(); ++i) {
            stringTags = stringTags + " " + QString::fromStdString(tags[i]);
            if(i!=tags.size()-1){
                stringTags = stringTags + ", " ;
            }
        }
        infosImages = infosImages + "Emplacement : " + chemin + "\nTaille : " + QString::number(size) + "Ko"
            + "\nDimensions : " + dimensionW + "x" + dimensionH + "\n" + stringTags + "\n" + "Album : " + album;
        infos->setText(infosImages );
    }
    previousIdPhoto = idPhoto;
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

