#include "bibliotheque.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <clickablelabel.h>
#include <assert.h>

class ClickableLabel;

Bibliotheque::Bibliotheque()
{
    idPhoto = 0;
    cout << "Création bibliotheque" << endl;
  //initDataFile(); // temporaire
 // addDirectory("../BibliothequePhoto/PicsTmp/");
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
              Image image(path, tags, idPhoto++);
              if(!image.getQImage()->isNull())
                listeImage.push_back(image);
          }
          else {
               Image image(line, idPhoto++);
                if(!image.getQImage()->isNull())
                    listeImage.push_back(image);
          }
        }
        myfile.close();
    }

    else cout << "Unable to open file" << endl;

   cout << "Nombre de photo : " << listeImage.size() << endl;
}

int Bibliotheque::getPositionImage(int idPhotoD) {
    int position;

    for(size_t i=0; i<listeImage.size(); i++) {
        if(listeImage[i].getId() == idPhotoD) {
            position = i;
            break;
        }
    }

    return position;
}

void Bibliotheque::updatePositionPhoto(int idPhotoD, int position) {
    Image m("",0);
    int index = 0;
    for(size_t i=0; i<listeImage.size(); i++) {
        if(listeImage[i].getId() == idPhotoD) {
            m = listeImage[i];
            index = i;
            cout << "trouve : " << i << endl;
            break;
        }
    }

    if(index < position) position--;
    listeImage.erase(listeImage.begin() + index);
    listeImage.insert(listeImage.begin()+position, m);
}

void Bibliotheque::removeImage(int idPhotoS) {
    for(size_t i=0; i<listeImage.size(); i++) {
        if(listeImage[i].getId() == idPhotoS) {
            cout << "Image supprimé ! " << endl;
            listeImage.erase(listeImage.begin() + i);
            break;
        }
    }
}

int Bibliotheque::getImgListSize(){
    return listeImage.size();
}

void Bibliotheque::deleteImgList(){
    listeImage.clear();
}

void Bibliotheque::fillDefaultTag(){

    for (int i = 0; i < listeImage.size() ; i++){

//        listeImage[i].addTag("default tag");
//        listeImage[i].addTag("default tag2");

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
        if(extension == "png" || extension == "jpg" || extension == "jpeg") {
            Image newImage(cheminDossier + ent->d_name, idPhoto++);
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
            Image newImage(cheminDossier +"/"+ ent->d_name, idPhoto++);
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

bool libContains(string path) {
    bool found = false;
    std::ifstream fileIn( "../BibliothequePhoto/images.csv");                   // Open for reading

    string buffer; // Store contents in a std::string
    string currentPath;

    while(getline(fileIn, buffer)) {
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

void Bibliotheque::addImage(Image image) {
    listeImage.push_back(image);
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

void Bibliotheque::addTag(int id, string tag) {
    for(unsigned int i = 0; i < listeImage.size(); i++) {
        Image &img = listeImage[i];
        if(img.getId() == id) {
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

    //cout << "New image of path " + filepath + " added to the library" << endl;
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

void Bibliotheque::setTagsListeImage(int image_pos, int tag_pos, std::string tag){

    listeImage[image_pos].setTag(tag_pos,tag);

}

std::vector<string> Bibliotheque::getAllTags()
{
    vector<string> tags;
    for(unsigned int i = 0; i < listeImage.size(); i++) {
        vector<string> tagsTmp = listeImage[i].getTags();
        for(unsigned int j = 0; j < tagsTmp.size(); j++) {
            if(std::find(tags.begin(), tags.end(), tagsTmp[j]) != tags.end()){

            } else {
                tags.push_back(tagsTmp[j]);
            }
        }
    }
    return tags;
}
