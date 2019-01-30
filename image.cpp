#include "image.h"

using namespace std;

Image::Image(string chemin)
{
    this->chemin = chemin;
    this->image = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        qDebug() << "Erreur lors de l'ouverture" << endl;
    }
}

Image::Image(string chemin, vector<string> tags)
{
    this->chemin    = chemin;
    this->tags      = tags;
    this->image     = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        qDebug() << "Erreur lors de l'ouverture" << endl;
    }
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

void Image::addTag(string tag) {
    this->tags.push_back(tag);
}

void Image::removeTags(){

    for(int i = 0 ; i < tags.size() ; i++)
     this->tags.pop_back();
}


void Image::removeTag(int indice){
    this->tags[indice] = "";
}
