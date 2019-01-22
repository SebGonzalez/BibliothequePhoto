#include "image.h"

using namespace std;

Image::Image(string cheminFichier)
{
    image = new QImage(QString::fromStdString(cheminFichier));
    if(image->isNull()) {
        cout << "Erreur lors de l'ouverture" << endl;
    }
}

QImage* Image::getQImage() {
    return image;
}
