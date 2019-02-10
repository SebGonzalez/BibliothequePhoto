#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <set>
#include "image.h"
#include <dirent.h>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QSizePolicy>
#include <algorithm>

using namespace std;

class Bibliotheque
{
public:
    Bibliotheque();
    void addDirectory(std::string cheminDossier);
    void loadImages();
    void drawImages(QFrame *frame, std::vector<Image> listeImage);
    void initDataFile();
    void addToFile(std::string filepath);
    void addToFile(std::string filepath, std::vector<std::string> tags);
    void addToFile(Image image);
    void addTag(std::string path, std::string tag);
    void addTag(int id, std::string tag);
    void addTags(std::string path, std::vector<std::string> tags);
    std::vector<Image> getTaggedImages(std::string tag);
    int  getImgListSize();
    std::vector<Image> getlisteImage();
    void addDirectoryArb(QFrame *frame, string cheminDossier);
    void fillDefaultTag();
    void deleteImgList();
    void updatePositionPhoto(int idPhotoD, int position);
    int getPositionImage(int idPhotoD);
    void addImage(Image image);
    void removeImage(int idPhotoS);
    void setTagsListeImage(int indice,int tag_indice,std::string newtag);
    std::vector<string> getAllTags();


private:
    std::vector<Image> listeImage;
    int idPhoto;

};

#endif // BIBLIOTHEQUE_H
