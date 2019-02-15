#include "bibliotheque.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>

class ClickableLabel;

Bibliotheque::Bibliotheque()
{
    fav_window = false;
    idPhoto = 0;
    cout << "Création bibliotheque" << endl;

    //initDataFile(); // temporaire
    //addDirectory("../BibliothequePhoto/PicsTmp/");

    loadImages();
}

void Bibliotheque::loadImages() {
    string line;

    ifstream myfile ("../BibliothequePhoto/images.csv");
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            std::size_t comma = line.find(",");

            string album = line.substr(0, comma);
            comma = comma + 2;
            std::size_t nextComma = line.find(',', comma);
            int fav = stoi(line.substr(comma, nextComma - comma));

            comma = comma + 3;
            nextComma = line.find(',', comma);
            if (nextComma != std::string::npos){ // if the image has tags
                vector<string> tags(0);
                // Parse path

                string path = line.substr(comma, nextComma - comma);
                // Parse tags
                comma = nextComma + 2;
                nextComma = line.find(',', comma);

                while(nextComma != std::string::npos) {
                    tags.push_back(line.substr(comma, nextComma - comma));
                    comma = nextComma + 2;
                    nextComma = line.find(',', comma);
                }
                tags.push_back(line.substr(comma, nextComma - comma));
                Image image(path, tags, idPhoto++, album, fav);
                if(!image.getQImage()->isNull())
                    listeImage.push_back(image);
            }
            else {
                string path = line.substr(comma, line.length()-comma);
                Image image(path, idPhoto++, album, fav);
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
    unsigned int position = 0;

    for(unsigned int i=0; i<listeImage.size(); i++) {
        if(listeImage[i].getId() == idPhotoD) {
            position = i;
            break;
        }
    }

    return static_cast<int>(position);
}

void Bibliotheque::updatePositionPhoto(int idPhotoD, int position) {
    Image *m = nullptr;
    unsigned int index = 0;
    for(unsigned int i=0; i<listeImage.size(); i++) {
        if(listeImage[i].getId() == idPhotoD) {
            m = &listeImage[i];
            index = i;
            break;
        }
    }

    if(index < static_cast<unsigned int>(position)) position--;
    listeImage.erase(listeImage.begin() + index);
    listeImage.insert(listeImage.begin()+position, *m);
}

void Bibliotheque::deleteTag(std::string tag){
    if(tag != ""){
        for(unsigned int i = 0 ; i < listeImage.size() ; i++){
            for(unsigned int j = 0 ; j < listeImage[i].getTags().size() ; j++){
                if(!listeImage[i].getTags()[j].compare(tag)){
                    listeImage[i].removeTag(tag);
                }
            }
        }
    }
}

void Bibliotheque::deleteTag(string tag, int i)
{
    unsigned int i2 = static_cast<unsigned int>(i);
    for(unsigned int j = 0 ; j < listeImage[i2].getTags().size() ; j++){
        if(!listeImage[i2].getTags()[j].compare(tag)){
            listeImage[i2].removeTag(tag);
        }
    }
}

void Bibliotheque::removeImage(int idPhotoS) {
    for(unsigned int i=0; i<listeImage.size(); i++) {
        if(listeImage[i].getId() == idPhotoS) {
            cout << "Image supprimé ! " << endl;
            listeImage.erase(listeImage.begin() + i);
            break;
        }
    }
}

int Bibliotheque::getImgListSize(){
    return static_cast<int>(listeImage.size());
}

void Bibliotheque::deleteImgList(){
    listeImage.clear();
}

std::vector<Image> Bibliotheque::getlisteImage(){
    return listeImage;
}

void Bibliotheque::addDirectory(string cheminDossier) {
    QString chemonDossierQt(cheminDossier.c_str());
    cout << "Lecture des fichiers : " << cheminDossier << endl;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (cheminDossier.c_str())) != nullptr) {
        while ((ent = readdir (dir)) != nullptr) {
            QString nomFichier(ent->d_name);
            string extension = nomFichier.section(".", -1).toStdString();
            if(extension == "png" || extension == "jpg" || extension == "jpeg") {
                Image newImage(cheminDossier + ent->d_name, idPhoto++, "NULL", 0);
                addToFile(cheminDossier + ent->d_name);
            }
        }
        closedir (dir);
    } else {
        perror ("Erreur lors de l'ouverture du dossier");
    }
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

std::string Bibliotheque::getChosenTag(){
    return this->chosen_tag;
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

vector<Image> Bibliotheque::getFavImages() {

    vector<Image> fav;
    for(unsigned int i = 0; i < listeImage.size(); i++) {
        Image img = listeImage[i];
        if(img.getFav() == true) fav.push_back(img) ;
    }

    return fav;

}


void Bibliotheque::setFav(int id){
    listeImage[static_cast<unsigned int>(id)].setFav();
}

void Bibliotheque::delFav(int id){
    listeImage[static_cast<unsigned int>(id)].delFav();
}


void Bibliotheque::addToFile(string filepath, vector<string> tags, string album, int fav) {
    if (libContains(filepath)) return;

    ofstream outfile;
    outfile.open("../BibliothequePhoto/images.csv", ios::app);
    assert (!outfile.fail());

    outfile << album << ", ";
    outfile << fav << ", ";
    outfile << filepath;
    for(unsigned int i = 0; i < tags.size(); i++) {
        outfile << ", " + tags[i];
    }
    outfile << endl;
    outfile.close();
}

void Bibliotheque::addToFile(string filepath) {
    vector<string> tags(0);
    string album = "NULL";
    addToFile(filepath, tags, album, 0);
}

void Bibliotheque::addToFile(Image image) {
    string path = image.getChemin();
    string album = image.getAlbum();
    vector<string> tags = image.getTags();

    addToFile(path, tags, album, image.getFav());
}

void Bibliotheque::initDataFile() {
    remove("../BibliothequePhoto/images.csv");
}

void Bibliotheque::setTagsListeImage(int image_pos, int tag_pos, std::string tag){

    listeImage[static_cast<unsigned int>(image_pos)].setTag(tag_pos,tag);

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

vector<string> Bibliotheque::getAllAlbums()
{
    vector<string> albums;
    for(unsigned int i = 0; i < listeImage.size(); i++) {
        string albumTmp = listeImage[i].getAlbum();
        if(albumTmp != "NULL" && !(find(albums.begin(), albums.end(), albumTmp) != albums.end() )) {
            albums.push_back(albumTmp);
        }
    }
    return albums;
}

bool Bibliotheque::isAlbum(string nom) {
    vector<string> albums = getAllAlbums();
    for (unsigned int i = 0; i < albums.size(); ++i) {
        if(nom == albums[i]) return true;
    }
    return false;

}

void Bibliotheque::updateCSV()
{
    initDataFile();
    for (unsigned int i = 0; i < listeImage.size(); ++i) {
        addToFile(listeImage[i]);
    }
}

long Bibliotheque::GetFileSize(Image img)
{
    struct stat stat_buf;
    int rc = stat(img.getChemin().c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

QSize Bibliotheque::getDimension(Image img)
{
    return img.getQImage()->size();
}

Image* Bibliotheque::getImageById(int id)
{
    for (unsigned int i = 0; i < listeImage.size(); ++i) {
        if(listeImage[i].getId() == id)
            return &listeImage[i];
    }
    return nullptr;
}

int Bibliotheque::position_from_list(std::vector<Image> listeImageFav,int position){

           string path = listeImage[static_cast<unsigned int>(position)].getPath();

           for(unsigned int i = 0 ; i < listeImageFav.size() ; i++)
               if(listeImageFav[i].getPath() == path)
                    return static_cast<int>(i);
    return -1;
}

