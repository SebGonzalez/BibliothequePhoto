#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <string>
#include <iostream>

class Image
{
public:
    Image(std::string chemin);

private:
    QImage image;
};

#endif // IMAGE_H
