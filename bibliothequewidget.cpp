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
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowContextMenu()));

     connect(timer, SIGNAL(timeout()), this, SLOT(displayLabel()));
    timer->start(1500);
    //connect(this, SIGNAL(itemEntered(QListWidgetItem* )), this, SLOT(displayLabel(QListWidgetItem* )));


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
        int nbPhotoParLigne =  this->width()/200 - 1;
        int idPhoto = currentItem()->data(Qt::UserRole+1).toInt();
        cout << "Widht : " << this->width() << " : " << nbPhotoParLigne << endl;
        QListWidgetItem *pieceItem = new QListWidgetItem();
     //   cout << "1"<< endl;
        pieceItem->setIcon(QIcon(pixmap.scaled(200,200)));
        pieceItem->setData(Qt::UserRole, QVariant(pixmap));
        pieceItem->setData(Qt::UserRole+1, QVariant(idPhoto));
        pieceItem->setData(Qt::UserRole+2, currentItem()->data(Qt::UserRole+2));
        pieceItem->setData(Qt::UserRole+3, currentItem()->data(Qt::UserRole+3));

        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

//        cout << "2"<< endl;
        int rowPhoto = ligne*nbPhotoParLigne + colonne+1;
        if(row(currentItem()) >= rowPhoto) {
            rowPhoto--;
        }
         //   cout << "3"<< endl;
        m_bibliotheque->updatePositionPhoto(idPhoto, rowPhoto);

    //     cout << "4"<< endl;


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

void BibliothequeWidget::refreshFavView(){

    this->clear();
    vector<Image> Img = m_bibliotheque->getFavImages();
    for(unsigned int i = 0; i < m_bibliotheque->getFavImages().size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*Img[i].getQImage());
        pixmap = pixmap.scaledToWidth(200);
        //pixmap.scaledToHeight(200);
        this->addPiece(pixmap.scaled(200,200), m_bibliotheque->getFavImages()[i].getId(),m_bibliotheque->getFavImages()[i].getTagsString());
    }

}


void BibliothequeWidget::ShowContextMenu()
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

    QAction del_fav("Supprimer des favoris");
    myMenu->addAction(&del_fav);

    QAction add_fav("Ajouter aux favoris");
    myMenu->addAction(&add_fav);

    if(m_bibliotheque->fav_window == true)
        myMenu->removeAction(&add_fav);


    else if(m_bibliotheque->fav_window == false)
        myMenu->removeAction(&del_fav);



    QAction* tagsMenu;
    for (unsigned int i = 0; i < listeTags.size(); ++i) {
        tagsMenu = addTag->addAction( QString::fromStdString(listeTags[i]));
        tagsMenu = deleteTag->addAction( "~" + QString::fromStdString(listeTags[i]));
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

        if(!QString::compare(selectedTag->iconText(),"Supprimer")) {
            confirmDelete *cd = new confirmDelete();
            cd->exec();
            if(cd->getValue() == true)
                for (int i = 0; i < listeItems.size(); ++i) {
                    int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                    m_bibliotheque->removeImage(idPhoto);
                }
                refreshView();
            delete cd;

        }
        else if(!QString::compare(selectedTag->iconText(),"Nouveau tag")){
            AjoutTagDialog *ajout = new AjoutTagDialog(this);
            ajout->exec();
            if(ajout->result() != 0){
                string addedTag = ajout->getValue().toStdString();
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
            refreshView();

        }
        else if(selectedTag == albumsMenu) {
            cout << "Nouvel album" << endl;
            AjoutTagDialog *ajout = new AjoutTagDialog(this);
            ajout->setObjectName("Ajout");
            ajout->exec();
            if(ajout->result() != 0){
                string addedAlbum = ajout->getValue().toStdString();
                if(addedAlbum.size() != 0){
                    for (int i = 0; i < listeItems.size(); i++) {
                        int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();

                        m_bibliotheque->getImageById(idPhoto)->setAlbum(addedAlbum);
                    }
                }
            }
            refreshView();

        }
        else if(selectedTag == supprimerAlbum) {

            for (int i = 0; i < listeItems.size(); i++) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();

                m_bibliotheque->getImageById(idPhoto)->setAlbum("NULL");
            }
            refreshView();


        }
        else if(!QString::compare(selectedTag->iconText(),"Ajouter aux favoris")) {

          //  cout << "oui" << endl;
            for (int i = 0; i < listeItems.size(); ++i) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                m_bibliotheque->getImageById(idPhoto)->setFav();

            }
            refreshView();

        }

        else if(!QString::compare(selectedTag->iconText(),"Supprimer des favoris")){
            for (int i = 0; i < listeItems.size(); ++i) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                m_bibliotheque->getImageById(idPhoto)->delFav();
            }
            refreshFavView();

        }
        else if(m_bibliotheque->isAlbum(selectedTag->iconText().toStdString())) {
            for (int i = 0; i < listeItems.size(); i++) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                string selectedAlbumToString = selectedTag->iconText().toStdString();
                m_bibliotheque->getImageById(idPhoto)->setAlbum(selectedAlbumToString);
            }
            refreshView();

        } else if (!QString::compare(selectedTag->iconText().at(0),"~")){
            QString tagTodDelete = selectedTag->iconText();
            tagTodDelete.remove(0,1);
            for (int i = 0; i < listeItems.size(); i++) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                m_bibliotheque->getImageById(idPhoto)->removeTag(tagTodDelete.toStdString());
            }
            refreshView();
        } else {

            string selectedTagToString = selectedTag->iconText().toStdString();
            for (int i = 0; i < listeItems.size(); ++i) {
                int idPhoto = listeItems[i]->data(Qt::UserRole+1).toInt();
                m_bibliotheque->addTag(idPhoto,selectedTagToString);
                QString text = listeItems[i]->data(Qt::UserRole+3).toString() + ", " + QString::fromStdString(selectedTagToString);
                if(listeItems[i]->data(Qt::UserRole+2).toString() != "")
                    listeItems[i]->setData(Qt::UserRole+2, text);
                listeItems[i]->setData(Qt::UserRole+3, text);
            }
            refreshView();

        }
        //   refreshView();

    }
}


void BibliothequeWidget::displayLabel()
{
    QPoint globalPos = this->mapFromGlobal(QCursor::pos());
    infos->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    infos->setStyleSheet("QLabel { background-color : white; color : black; }");

    int nbPhotoParLigne =  this->width()/200 - 1;
    infos->setGeometry(globalPos.x(),globalPos.y(),500,100);
    if(infos->text().size() != 0 && globalPos.x() < nbPhotoParLigne*215){
        infos->show();
    }
    else
        infos->hide();
    connect(this, SIGNAL(itemEntered(QListWidgetItem* )), this, SLOT(displayLabel2(QListWidgetItem* )));
}

void BibliothequeWidget::displayLabel2(QListWidgetItem* item)
{
    timer->start(1500);
    int idPhoto = item->data(Qt::UserRole+1).toInt();
    if(idPhoto != previousIdPhoto){
        infos->hide();
        QString infosImages ;
        Image *Img = m_bibliotheque->getImageById(idPhoto);
        QString chemin = QString::fromStdString( Img->getChemin());
        QString album = QString::fromStdString( Img->getAlbum());
        double size = m_bibliotheque->GetFileSize(*Img)/1000;
        QSize dimension = m_bibliotheque->getDimension(*Img);
        QString dimensionW = QString::number(dimension.width());
        QString dimensionH = QString::number(dimension.height());
        vector <string> tags = Img->getTags();
        QString stringTags = "Tags : ";
        for (unsigned int i = 0; i < tags.size(); ++i) {
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
void BibliothequeWidget::hideLabel() {
    infos->hide();
}

void BibliothequeWidget::startDrag(Qt::DropActions)
{
    if(m_bibliotheque->fav_window == false){
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
}

