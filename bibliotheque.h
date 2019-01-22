#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <vector>
#include "image.h"

class Bibliotheque
{
public:
    Bibliotheque();
    void loadImage(std::string cheminDossier);
    void save();

private:
    std::vector<Image> listeImage;
};

#endif // BIBLIOTHEQUE_H
