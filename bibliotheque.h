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
#include <sys/stat.h>

using namespace std;

class Bibliotheque
{
public:
    bool fav_window;
    Bibliotheque();
    void addDirectory(std::string cheminDossier);
    void loadImages();
    void drawImages(QFrame *frame, std::vector<Image> listeImage);
    void initDataFile();
    void addToFile(std::string filepath);
    void addToFile(std::string filepath, std::vector<std::string> tags, std::string album, int fav);
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
    std::vector<string> getAllAlbums();
    bool isAlbum(std::string nom);
    void updateCSV();

    std::string getChosenTag();
    std::string setChosenTag(std::string tag);
    void deleteTag(std::string tag);
    void deleteTag(std::string tag,int i);
    std::vector<Image> getFavImages();
    void setFav(int id);
    void delFav(int id);


    long GetFileSize(Image img);
    QSize getDimension(Image img);
    Image* getImageById(int id);

private:
    std::vector<Image> listeImage;
    int idPhoto;
    std::string chosen_tag;

};

#endif // BIBLIOTHEQUE_H
