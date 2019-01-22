#include "image.h"

using namespace std;

Image::Image(string cheminFichier)
{
    image.load(QString::fromStdString(cheminFichier));
    if(image.isNull()) {
        cout << "Erreur lors de l'ouverture" << endl;
    }
}
