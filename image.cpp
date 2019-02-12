#include "image.h"

using namespace std;

Image::Image(string chemin, int id)
{
    this->id = id;
    this->chemin = chemin;
    this->image = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        qDebug() << "Erreur lors de l'ouverture" << endl;
    }
}

Image::Image(string chemin, vector<string> tags, int id)
{
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
