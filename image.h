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
    Image(std::string chemin, int id, std::string album, int fav);
    Image(std::string chemin, std::vector<std::string> tags, int id, std::string album, int fav);
    int getId();
    QImage* getQImage();
    std::string getChemin();
    std::string getAlbum();
    void setAlbum(std::string album);
    std::vector<std::string> getTags();
    std::string getTagsString();
    void addTag(std::string tag);
    void removeTags();
    void removeTag(int indice);
    void removeTag(std::string );
    void setTag(int indice,std::string string);
    void setFav();
    void delFav();
    int  getFav();
    std::string getPath();


private:
    int id;
    std::string chemin;
    std::vector<std::string> tags;
    std::string album;
    QImage *image;
    int fav;
};

#endif // IMAGE_H
