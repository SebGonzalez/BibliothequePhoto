#include "image.h"

using namespace std;

Image::Image(string chemin)
{
    this->chemin = chemin;
    this->image = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        cout << "Erreur lors de l'ouverture" << endl;
    }
}

Image::Image(string chemin, vector<string> tags)
{
    this->chemin    = chemin;
    this->tags      = tags;
    this->image     = new QImage(QString::fromStdString(chemin));
    if(image->isNull()) {
        cout << "Erreur lors de l'ouverture" << endl;
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
