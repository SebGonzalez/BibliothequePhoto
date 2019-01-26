#include "bibliotheque.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <clickablelabel.h>

using namespace std;
class ClickableLabel;

Bibliotheque::Bibliotheque()
{
    initDataFile();
    cout << "Création bibliotheque" << endl;
    addDirectory("../BibliothequePhoto/PicsTmp/");
    loadImages();
}

void Bibliotheque::loadImages() {
    string line;
    ifstream myfile ("../BibliothequePhoto/images.csv");
    if (myfile.is_open()) {
        while (getline (myfile,line)) {
          std::size_t comma = line.find(",");
          if (comma != std::string::npos){ // S'il y a une virgule dans line on prend la substring avant elle.
              string str = line.substr(0, comma);
              listeImage.push_back(str);
          }
          else {
              listeImage.push_back(line);
          }
        }
        myfile.close();
    }

    else cout << "Unable to open file";

}

int Bibliotheque::getImgListSize(){
    return listeImage.size();
}

std::vector<Image> Bibliotheque::getlisteImage(){
    return listeImage;
}

void Bibliotheque::addDirectory(string cheminDossier) {
    QString chemonDossierQt(cheminDossier.c_str());
    cout << "Lecture des fichiers : " << cheminDossier << endl;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (cheminDossier.c_str())) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        QString nomFichier(ent->d_name);
        string extension = nomFichier.section(".", -1).toStdString();
        if(extension == "png" || extension == "jpg") {
            Image newImage(cheminDossier + ent->d_name);
            addToLib(cheminDossier + ent->d_name);
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
    for(unsigned int i = 0; i < listeImage.size(); i++) {
        QPixmap pixmap = QPixmap::fromImage(*listeImage[i].getQImage());
        ClickableLabel *imgDisplayLabel = new ClickableLabel();
        imgDisplayLabel->setPixmap(pixmap.scaled(200,200));
        imgDisplayLabel->setFixedWidth(200);
        imgDisplayLabel->setFixedHeight(200);
           layout->addWidget(imgDisplayLabel, line, colonne);
           colonne++;
           if(colonne ==5) {
               line++;
               colonne = 0;
           }


    }
    layout->minimumSize().setHeight(line*210);
    layout->maximumSize().setHeight(line*210);
}


bool libContains(string path) {
    bool found = false;
    std::ifstream fileIn( "../BibliothequePhoto/images.dat");                   // Open for reading

    string buffer; // Store contents in a std::string
    string currentPath;

    while(getline(fileIn, buffer)) {
        cout << buffer << endl;
        if (buffer.find(path) != std::string::npos) {
            found = true;
            break;
        }
    }
    fileIn.close();
    if (found) {
        cout << "Your library contains this file" << endl;
        return true;
    }
    else {
        return false;
    }


}

void Bibliotheque::addTag(string path, string tag) {
    for(unsigned int i = 0; i < listeImage.size(); i++) {
        Image &img = listeImage[i];
        if(img.getChemin().compare(path) == 0) {
            img.addTag(tag);
            return;
        }
    }
}

void Bibliotheque::addTags(string path, vector<string> tags) {
    for(unsigned int i = 0; i < listeImage.size(); i++) {
        Image &img = listeImage[i];
        if(img.getChemin().compare(path) == 0) {
            for(unsigned int j = 0; j < tags.size(); j++) {
                img.addTag(tags[j]);
            }
            return;
        }
    }
}

//void Bibliotheque::addToLib(string filepath) {
//    ofstream outfile;
//    bool comma = false;

//    if (!emptyDataFile()) comma = true;
//    if (libContains(filepath)) {
//        return;
//    }

//    openJson();
//    outfile.open("../BibliothequePhoto/images.dat", ios::app);

//    assert (!outfile.fail());
//    if (comma) addComma();
//    string img;
//    img = "\t{\n\t\t\"path\" : \"" + filepath + "\",\n";
//    img = img + "\t\t\"tags\" : [\n\t\t]";
//    outfile << img << "\n\t}" << endl;

//    outfile.close();
//    sealJson();

//    cout << "New image of path " + filepath + " added to the library";
//}

void Bibliotheque::addToLib(string filepath) {
    if (libContains(filepath)) return;

    ofstream outfile;
    outfile.open("../BibliothequePhoto/images.csv", ios::app);
    assert (!outfile.fail());
    outfile << filepath << endl;
    outfile.close();

    cout << "New image of path " + filepath + " added to the library" << endl;
}

void Bibliotheque::addToLib(string filepath, vector<string> tags) {
    if (libContains(filepath)) return;

    ofstream outfile;
    outfile.open("../BibliothequePhoto/images.csv", ios::app);
    assert (!outfile.fail());
    outfile << filepath;
    for(unsigned int i = 0; i < tags.size(); i++) {
        outfile << ", " + tags[i];
    }
    outfile << endl;
    outfile.close();

    cout << "New image of path " + filepath + " added to the library" << endl;
}

//void Bibliotheque::initDataFile() {
//    string line;
//    ifstream myfile ("../BibliothequePhoto/images.dat");
//    if (myfile.is_open()) {
//        if (!getline (myfile,line)) {
//            myfile.close();
//            ofstream outfile;
//            outfile.open("../BibliothequePhoto/images.dat");
//            outfile << "{" << endl << "}";
//            cout << "Data file initialized." << endl;
//        }
//        else {
//            cout << "Data file already initialized." << endl;
//        }
//        myfile.close();
//    }

//    else cout << "Unable to open file";
//}

void Bibliotheque::initDataFile() {
    remove("../BibliothequePhoto/images.csv");
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


