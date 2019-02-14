#include "albumdialog.h"
#include "ui_albumDialog.h"

AlbumDialog::AlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlbumDialog)
{
    ui->setupUi(this);
    setFixedSize(868,482);
}

AlbumDialog::AlbumDialog(Bibliotheque &bibliotheque, BibliothequeWidget &bibliothequeWidget):
   ui(new Ui::AlbumDialog)
{
    ui->setupUi(this);
    this->bibliotheque = &bibliotheque;
    this->bibliothequeWidget = &bibliothequeWidget;

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    vector<string> albums = this->bibliotheque->getAllAlbums();
    for(unsigned int i=0; i<albums.size(); i++) {
       QListWidgetItem *pieceItem = new QListWidgetItem( ui->listWidget);
       pieceItem->setText(albums[i].c_str());
    }

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(acceptedSlot()));

}

AlbumDialog::~AlbumDialog()
{
    delete ui;
}

void AlbumDialog::acceptedSlot() {
    bibliothequeWidget->clear();

    QList<QListWidgetItem*> listeItems = ui->listWidget->selectedItems();
    for(unsigned int i = 0; i<bibliotheque->getlisteImage().size(); i++) {
         for (int y = 0; y < listeItems.size(); y++) {
             cout << listeItems[y]->text().toStdString() << " : " << bibliotheque->getlisteImage()[i].getAlbum() << endl;
             if(listeItems[y]->text().toStdString() == bibliotheque->getlisteImage()[i].getAlbum()) {
                 QPixmap pixmap = QPixmap::fromImage(*bibliotheque->getlisteImage()[i].getQImage());
                 pixmap = pixmap.scaledToWidth(200);
                 //pixmap.scaledToHeight(200);
                 bibliothequeWidget->addPiece(pixmap.scaled(200,200), bibliotheque->getlisteImage()[i].getId(), bibliotheque->getlisteImage()[i].getTagsString());
             }

         }
    }
}

void AlbumDialog::rejectedSlot() {
    cout << "non" << endl;
}
