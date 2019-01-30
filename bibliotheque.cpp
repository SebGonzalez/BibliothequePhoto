#include "bibliotheque.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <clickablelabel.h>
#include <assert.h>

class ClickableLabel;

Bibliotheque::Bibliotheque()
{
    cout << "Création bibliotheque" << endl;
    //initDataFile(); // temporaire
    //addDirectory("../BibliothequePhoto/PicsTmp/");
    loadImages();
    fillDefaultTag();
}

void Bibliotheque::loadImages() {
    string line;

    ifstream myfile ("../BibliothequePhoto/images.csv");
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
          std::size_t comma = line.find(",");
          if (comma != std::string::npos){ // if the image has tags
              vector<string> tags(0);
              // Parse path
              string path = line.substr(0, comma);

              // Parse tags
              comma = comma + 2;
              std::size_t nextComma = line.find(',', comma);
              while(nextComma != std::string::npos) {
                  tags.push_back(line.substr(comma, nextComma - comma));
                  comma = nextComma + 2;
                  nextComma = line.find(',', comma);
              }
              tags.push_back(line.substr(comma, nextComma - comma));

              Image image(path, tags);
              listeImage.push_back(image);
          }
          else {
              listeImage.push_back(line);
          }
        }
        myfile.close();
    }

    else cout << "Unable to open file" << endl;

    for (int i = 0; i < listeImage.size(); i++) {
        cout << listeImage[i].getChemin() + " - ";
        for(int j = 0; j < listeImage[i].getTags().size(); j++) {
            cout << "tag : " + listeImage[i].getTags()[j] << endl;
        }
        cout << endl;
    }
}

int Bibliotheque::getImgListSize(){
    return listeImage.size();
}

void Bibliotheque::deleteImgList(){
    listeImage.empty();
}

void Bibliotheque::fillDefaultTag(){

    for (int i = 0; i < listeImage.size() ; i++){

        listeImage[i].addTag("default tag");
        listeImage[i].addTag("default tag2");

    }
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
            addToFile(cheminDossier + ent->d_name);
        }
      }
      closedir (dir);
    } else {
      perror ("Erreur lors de l'ouverture du dossier");
    }
}

void Bibliotheque::addDirectoryArb(QFrame *frame, string cheminDossier) {
    cout << "Lecture des fichiers : " << cheminDossier << endl;
    DIR *dir;
    struct dirent *ent;
    vector<Image> images;
    if ((dir = opendir (cheminDossier.c_str())) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        QString nomFichier(ent->d_name);
        string extension = nomFichier.section(".", -1).toStdString();
        if(extension == "png" || extension == "jpg") {
            cout << cheminDossier << ent->d_name << endl;
            Image newImage(cheminDossier +"/"+ ent->d_name );
            newImage.addTag("default tag");
            newImage.addTag("default tag2");
            images.push_back(newImage);

        }
      }
      closedir (dir);
    } else {
      perror ("Erreur lors de l'ouverture du dossier");
    }

    listeImage = images;
}

//void Bibliotheque::drawImages(QFrame *frame, vector<Image> listeImage) {
//    int line = 0;
//    int colonne = 0;
//    for(unsigned int i = 0; i < listeImage.size(); i++) {
//        QPixmap pixmap = QPixmap::fromImage(*listeImage[i].getQImage());
//        ClickableLabel *imgDisplayLabel = new ClickableLabel();
//        imgDisplayLabel->setPixmap(pixmap.scaled(200,200));
//        imgDisplayLabel->setFixedWidth(200);
//        imgDisplayLabel->setFixedHeight(200);
//        frame->addWidget(imgDisplayLabel, line, colonne);
//        colonne++;
//        if(colonne ==5) {
//            line++;
//            colonne = 0;
//        }
//    }
//    frame->minimumSize().setHeight(line*210);
//    frame->maximumSize().setHeight(line*210);
//}


bool libContains(string path) {
    bool found = false;
    std::ifstream fileIn( "../BibliothequePhoto/images.csv");                   // Open for reading

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
    if (found) {https://github.com/SebGonzalez/BibliothequePhoto/commit/64a20293686c1ea971ecddb7dedbfcec115691a6mage
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

vector<Image> Bibliotheque::getTaggedImages(string tag) {
    vector<Image> tagged;

    for(unsigned int i = 0; i < listeImage.size(); i++) {
        Image img = listeImage[i];
        vector<string> tags = img.getTags();
        for(unsigned int j = 0; j < tags.size(); j++) {
            if(tags[j].compare(tag) == 0)
                tagged.push_back(img);
        }
    }

    return tagged;
}

void Bibliotheque::addToFile(string filepath, vector<string> tags) {
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

void Bibliotheque::addToFile(string filepath) {
    vector<string> tags(0);
    addToFile(filepath, tags);
}

void Bibliotheque::addToFile(Image image) {
    string path = image.getChemin();
    vector<string> tags = image.getTags();

    addToFile(path, tags);
}

void Bibliotheque::initDataFile() {
    remove("../BibliothequePhoto/images.csv");
}
