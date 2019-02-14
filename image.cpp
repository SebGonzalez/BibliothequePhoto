#include "image.h"
#include <vector>
#include <iostream>
using namespace std;

Image::Image(string chemin, int id, string album)
{
    this->album = album;
    this->id = id;
    this->chemin = chemin;
    this->image = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        qDebug() << "Erreur lors de l'ouverture" << endl;
    }
}

Image::Image(string chemin, vector<string> tags, int id, string album)
{
    this->album = album;
    this->id = id;
    this->chemin    = chemin;
    this->tags      = tags;
    this->image     = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        qDebug() << "Erreur lors de l'ouverture" << endl;
    }
}

void Image::setTag(int indice, std::string string){

    this->tags[indice] = string;

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
        for(int i=1; i<tags.size(); i++) {
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

    for(int i = 0 ; i < tags.size() ; i++)
     this->tags.pop_back();
}


void Image::removeTag(int indice){
    this->tags[indice] = "";
}

void Image::removeTag(std::string tag){

     //std::vector<std::string> tags;
    std::vector <std::string> tag_2;
    for(int i = 0 ; i < tags.size() ; i++ ){
        if(tags[i].compare(tag))
        tag_2.push_back(tags[i]);
        }

    tags.clear();


    for(int i = 0 ; i < tag_2.size() ; i++){
        tags.push_back(tag_2[i]);
    }
}
