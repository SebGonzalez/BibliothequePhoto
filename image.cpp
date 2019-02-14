#include "image.h"
#include <vector>
#include <iostream>
using namespace std;

Image::Image(string chemin, int id, string album, int fav)
{
    this->album = album;
    this->id = id;
    this->chemin = chemin;
    this->image = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        qDebug() << "Erreur lors de l'ouverture" << endl;
    }
    this->fav = fav;
}

Image::Image(string chemin, vector<string> tags, int id, string album, int fav)
{
    this->album = album;
    this->id = id;
    this->chemin    = chemin;
    this->tags      = tags;
    this->image     = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        qDebug() << "Erreur lors de l'ouverture" << endl;
    }

     this->fav = fav;
}

void Image::setTag(int indice, std::string string){
    this->tags[static_cast<size_t>(indice)] = string;

}

int Image::getId() {
    return this->id;
}

QImage* Image::getQImage() {
    return this->image;
}

string Image::getChemin() {
    return this->chemin;
}

string Image::getAlbum() {
    return this->album;
}

void Image::setAlbum(string album) {
    cout << "Album changé : " << album << endl;
   this->album = album;
}

vector<string> Image::getTags() {
    return this->tags;
}

string Image::getTagsString() {
    if(tags.size() > 0) {
        string textTag = tags[0];
        for(unsigned int i=1; i<tags.size(); i++) {
          textTag += ", " + tags[i];
         }
        return textTag;
    }
    return "";
}

void Image::addTag(string tag) {
    if(!(std::find(this->tags.begin(), this->tags.end(), tag) != this->tags.end()))
        this->tags.push_back(tag);
}

void Image::removeTags(){

    for(unsigned int i = 0 ; i < tags.size() ; i++)
     this->tags.pop_back();
}


void Image::removeTag(int indice){
    this->tags[static_cast<size_t>(indice)] = "";
}

void Image::removeTag(std::string tag){

     //std::vector<std::string> tags;
    std::vector <std::string> tag_2;
    for(unsigned int i = 0 ; i < tags.size() ; i++ ){
        if(tags[i].compare(tag))
        tag_2.push_back(tags[i]);
        }

    tags.clear();


    for(unsigned int i = 0 ; i < tag_2.size() ; i++){
        tags.push_back(tag_2[i]);
    }
}

int Image::getFav(){
    return this->fav;
}

void Image::setFav(){
    this->fav = true;

}

void Image::delFav(){
    this->fav = false;
}
