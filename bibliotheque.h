#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <vector>
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
    void loadImage(std::string cheminDossier);
    void save();
    void drawImages(QGridLayout *layout);
    void addToLib(std::string filepath);

private:
    std::vector<Image> listeImage;
};

#endif // BIBLIOTHEQUE_H
