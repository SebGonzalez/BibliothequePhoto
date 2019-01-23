#include "bibliotheque.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Bibliotheque::Bibliotheque()
{
    initDataFile();
    addToLib("image.jpg");
    addToLib("image2.jpg");
    addToLib("image.jpg");
    std::cin.get();
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


bool emptyDataFile() {
    string line1, line2;
    ifstream myfile ("../BibliothequePhoto/images.dat");
    if (myfile.is_open()) {
        getline (myfile, line1);
        getline (myfile, line2);
        myfile.close();

        if (line2.compare("}") == 0) {
            cout << "Data file is empty." << endl;
            return true;
        }
    }
    return false;
}


bool libContains(string path) {
    bool found = false;
    std::ifstream fileIn( "../BibliothequePhoto/images.dat");                   // Open for reading

    string buffer; // Store contents in a std::string
    string currentPath;

    while(getline(fileIn, buffer)) {
        cout << buffer << endl;
        if (buffer.find(path) != std::string::npos) {
            cout << "Already exists!" << endl;
            found = true;
            break;
        }
    }
    fileIn.close();
    if (found) {
        cout << "Your library already contains this file" << endl;
        return true;
    }
    else {
        return false;
    }


}

void addTag(string path, string tag) {
    if (!libContains(path)) {
        cout << "Cannot add tag ; invalid path.\n";
        return;
    }

}

void Bibliotheque::addToLib(string filepath) {
    ofstream outfile;
    bool comma = false;

    if (!emptyDataFile()) comma = true;
    if (libContains(filepath)) {
        return;
    }

    openJson();
    outfile.open("../BibliothequePhoto/images.dat", ios::app);

    assert (!outfile.fail());
    if (comma) addComma();
    string img;
    img = "\t{\n\t\t\"path\" : \"" + filepath + "\",\n";
    img = img + "\t\t\"tags\" : [\n\t\t]";
    outfile << img << "\n\t}" << endl;

    outfile.close();
    sealJson();

    cout << "New image of path " + filepath + " added to the library";
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
            cout << "Data file initialized." << endl;
        }
        else {
            cout << "Data file already initialized." << endl;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

void Bibliotheque::addComma() {
    std::ifstream fileIn( "../BibliothequePhoto/images.dat" );                   // Open for reading

    std::stringstream buffer;                             // Store contents in a std::string
    buffer << fileIn.rdbuf();
    std::string contents = buffer.str();

    fileIn.close();
    contents.pop_back();                                  // Remove last character
    contents.pop_back();                                  // Remove last character
    contents = contents + ",\n";
    std::ofstream fileOut( "../BibliothequePhoto/images.dat" , std::ios::trunc); // Open for writing (while also clearing file)
    fileOut << contents;                                  // Output contents with removed character
    fileOut.close();
}

void Bibliotheque::openJson() {
    std::ifstream fileIn( "../BibliothequePhoto/images.dat" );                   // Open for reading

    std::stringstream buffer;                             // Store contents in a std::string
    buffer << fileIn.rdbuf();
    std::string contents = buffer.str();

    fileIn.close();
    contents.pop_back();                                  // Remove last character

    std::ofstream fileOut( "../BibliothequePhoto/images.dat" , std::ios::trunc); // Open for writing (while also clearing file)
    fileOut << contents;                                  // Output contents with removed character
    fileOut.close();
}

void Bibliotheque::sealJson() {
    ofstream outfile;

    outfile.open("../BibliothequePhoto/images.dat", ios::app);

    outfile << "}" << endl;

    outfile.close();
}


