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
    cout << "oui" << endl;
}

void AlbumDialog::rejectedSlot() {
    cout << "non" << endl;
}
