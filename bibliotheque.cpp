#include "bibliotheque.h"
#include <fstream>
#include <iostream>

using namespace std;

Bibliotheque::Bibliotheque()
{
    initDataFile();
    cout << "Création bibliotheque" << endl;
    loadImage("../BibliothequePhoto/PicsTmp/");
    //loadImage("PicsTmp/");
}

void Bibliotheque::loadImage(string cheminDossier) {
    QString chemonDossierQt(cheminDossier.c_str());
    cout << "Lecture des fichiers : " << cheminDossier << endl;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (cheminDossier.c_str())) != NULL) {
      while ((ent = readdir (dir)) != NULL) {

        QString nomFichier(ent->d_name);
      //  cout << "oui : " << cheminFichier.toStdString() << " : " << cheminFichier.section(".", -1).toStdString() << endl;
        if(nomFichier.section(".", -1).toStdString() == "png" ||  nomFichier.section(".", -1).toStdString() == "jpg") {
           // printf ("HEY %s\n", ent->d_name);
            Image newImage(cheminDossier + ent->d_name);
            listeImage.push_back(newImage);
        }
      }
      closedir (dir);
    } else {
      perror ("Erreur lors de l'ouverture du dossier");
    }
}

void Bibliotheque::drawImages(QGridLayout *layout) {
    int line = 0;
    int colonne = 0;
    for(int i = 0; i < listeImage.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*listeImage[i].getQImage());
        QLabel *imgDisplayLabel = new QLabel("");
        imgDisplayLabel->setPixmap(pixmap.scaled(200,200));
        imgDisplayLabel->adjustSize();
        imgDisplayLabel->setFixedWidth(200);
       imgDisplayLabel->setFixedHeight(200);
           layout->addWidget(imgDisplayLabel, line, colonne);
           colonne++;
           if(colonne == 5) {
               line++;
               colonne = 0;
           }
    }
     layout->minimumSize().setHeight(line*210);
    layout->maximumSize().setHeight(line*210);
}

void Bibliotheque::addToLib(string filepath) {
    ofstream outfile;

    outfile.open("../BibliothequePhoto/images.dat", ios::app);

    assert (!outfile.fail());
    string img;
    img = "{\n\t\"path\" : \"" + filepath + "\",\n";
    img = img + "\t\"tags\" : [\n\t]";
    outfile << img << "\n}" << endl;

    outfile.close();
}

void Bibliotheque::initDataFile() {
    string line;
    ifstream myfile ("../BibliothequePhoto/images.dat");
    if (myfile.is_open()) {
        if (!getline (myfile,line)) {
            myfile.close();
            ofstream outfile;
            outfile.open("../BibliothequePhoto/images.dat");
            outfile << "{" << endl << "}";
        }
        else {
            cout << "Fichier déjà initialisé.";
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}
