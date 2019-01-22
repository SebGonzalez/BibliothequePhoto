#include "bibliotheque.h"

#include <filesystem>

using namespace std;

Bibliotheque::Bibliotheque()
{
    cout << "Création bibliotheque" << endl;
    loadImage("D:/GoogleDrive/Master/S2/IHM/Projet/BibliothePhoto/PicsTmp");
}

void Bibliotheque::loadImage(string cheminDossier) {
    cout << "Lecture des fichiers : " << cheminDossier << endl;
    for (const auto & entry : filesystem::directory_iterator(cheminDossier))
            std::cout << "oui : " << entry.path() << std::endl;
    //listeImage.push_back();
}
