#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <set>
#include "image.h"
#include <dirent.h>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QSizePolicy>

class Bibliotheque
{
public:
    Bibliotheque();
    void addDirectory(std::string cheminDossier);
    void loadImages();
    void drawImages(QGridLayout *layout, std::vector<Image> listeImage);
    void initDataFile();
    void addToFile(std::string filepath);
    void addToFile(std::string filepath, std::vector<std::string> tags);
    void addToFile(Image image);
    void addTag(std::string path, std::string tag);
    void addTags(std::string path, std::vector<std::string> tags);
    std::vector<Image> getTaggedImages(std::string tag);
    int  getImgListSize();
    std::vector<Image> getlisteImage();

private:
    std::vector<Image> listeImage;

};

#endif // BIBLIOTHEQUE_H
