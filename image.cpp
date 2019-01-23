#include "image.h"

using namespace std;

Image::Image(string chemin)
{
    this->chemin = chemin;
    this->image = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        cout << "Erreur lors de l'ouverture" << endl;
    }
}

QImage* Image::getQImage() {
    return this->image;
}

string Image::getChemin() {
    return this->chemin;
}
