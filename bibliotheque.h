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
