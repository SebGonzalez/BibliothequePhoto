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
    void save();
    void loadImages();
    void drawImages(QGridLayout *layout);
    void addToLib(std::string filepath);
    void addToLib(std::string filepath, std::vector<std::string> tags);
    void addTag(std::string path, std::string tag);
    void addTags(std::string path, std::vector<std::string> tags);
    int getImgListSize();
    std::vector<Image> getlisteImage();

private:
    std::vector<Image> listeImage;
    void initDataFile();
    void openJson();
    void sealJson();
    void addComma();

};

#endif // BIBLIOTHEQUE_H
