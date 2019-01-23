#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <string>
#include <iostream>
#include <set>

class Image
{
public:
    Image(std::string chemin);
    QImage* getQImage();
    std::string getChemin();

private:
    std::string chemin;
    std::vector<std::string> tags;
    QImage *image;
};

#endif // IMAGE_H
