#include <fstream>
#include <iostream>
#include "Image.h"

using namespace std;

void Image::loadImage(string filePath) {
    ifstream File(filePath, ios_base::binary);

    //load image properties
    File.read(&header.idLength, sizeof(header.idLength));
    File.read(&header.colorMapType, sizeof(header.colorMapType));
    File.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    File.read((char *)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    File.read((char *)&header.colorMapLength, sizeof(header.colorMapLength));
    File.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
    File.read((char *)&header.xOrigin, sizeof(header.xOrigin));
    File.read((char *)&header.yOrigin, sizeof(header.yOrigin));
    File.read((char *)&header.width, sizeof(header.width));
    File.read((char *)&header.height, sizeof(header.height));
    File.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    File.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

    //reading pixels
    int size = header.height * header.width;
    int currentPixel = 0;
    while (currentPixel < size) {
        Pixel pixel;

        File.read((char*)&pixel.blue, sizeof(pixel.blue));
        File.read((char*)&pixel.green, sizeof(pixel.green));
        File.read((char*)&pixel.red, sizeof(pixel.red));
        
        pixels.push_back(pixel);
        currentPixel++;
    }
    File.close();

}