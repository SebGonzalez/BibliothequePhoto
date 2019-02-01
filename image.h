#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <string>
#include <iostream>
#include <set>
#include <qdebug.h>

class Image
{
public:
    Image(std::string chemin, int id);
    Image(std::string chemin, std::vector<std::string> tags, int id);
    int getId();
    QImage* getQImage();
    std::string getChemin();
    std::vector<std::string> getTags();
    void addTag(std::string tag);
    void removeTags();
    void removeTag(int indice);
    void setTag(int indice,std::string string);

private:
    int id;
    std::string chemin;
    std::vector<std::string> tags;
    QImage *image;
};

#endif // IMAGE_H
