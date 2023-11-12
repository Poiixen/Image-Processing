#include <fstream>
#include <iostream>
#include "Image.h"

using namespace std;

float Image::scale(float scale) {
    scale += 0.5f;
    return scale;
}

vector<Pixel> Image::getPixels() {
    return pixels;
}

Image::Header Image::getHeader() {
    return header;
}

unsigned int Image::CharToInt(unsigned char character) {
    return (unsigned int)(character - '\0');
}

unsigned char Image::IntToChar(unsigned int integer) {
    return (unsigned char)(integer + '\0');
}

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
    unsigned int totalPixels = header.height * header.width;
    for (unsigned int i = 0; i < totalPixels; i++)
    {
        Pixel pixel;
        File.read((char *)&pixel.blue, sizeof(pixel.blue));
        File.read((char *)&pixel.green, sizeof(pixel.green));
        File.read((char *)&pixel.red, sizeof(pixel.red));

        pixel.blueint = CharToInt(pixel.blue);
        pixel.greenint = CharToInt(pixel.green);
        pixel.redint = CharToInt(pixel.red);
        pixels.push_back(pixel);
    }
    File.close();


}

void Image::writeImage(string filepath) {
    
    ofstream File(filepath, ios_base::binary);

    if (File.is_open()) {

        File.write(&header.idLength, sizeof(header.idLength));
        File.write(&header.colorMapType, sizeof(header.colorMapType));
        File.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        File.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        File.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        File.write(&header.colorMapDepth, sizeof(header.colorMapDepth));

        File.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        File.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        File.write((char*)&header.width, sizeof(header.width));
        File.write((char*)&header.height, sizeof(header.height));
        File.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        File.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
        
        for (unsigned int i = 0; i < pixels.size(); i++) {
            File.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));
            File.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));
            File.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));
        }
        File.close();
    }
}

void Image::setUnsignedInts() {
    for (unsigned int i = 0; i < pixels.size(); i++)
    {
        pixels[i].redint = CharToInt(pixels[i].red);
        pixels[i].greenint = CharToInt(pixels[i].green);
        pixels[i].blueint = CharToInt(pixels[i].blue);
    }
}

void Image::setPixels(vector<Pixel> &vector) {
    for (unsigned int i = 0; i < vector.size(); i++)
    {
        pixels.push_back(vector[i]);
    }
}

void Image::setHeader(Header headerData) {
    header.idLength = headerData.idLength;
    header.colorMapType = headerData.colorMapType;
    header.dataTypeCode = headerData.dataTypeCode;
    header.colorMapOrigin = headerData.colorMapOrigin;
    header.colorMapLength = headerData.colorMapLength;
    header.colorMapDepth = headerData.colorMapDepth;
    header.xOrigin = headerData.xOrigin;
    header.yOrigin = headerData.yOrigin;
    header.width = headerData.width;
    header.height = headerData.height;
    header.bitsPerPixel = headerData.bitsPerPixel;
    header.imageDescriptor = headerData.imageDescriptor;
}


/************************************************************************/

Image Image::Multiply(Image &img1, Image &img2) {
    
    Image resultImg;
    Image::setHeader(img1.getHeader());

    resultImg.setHeader(header);
    img1.setUnsignedInts();
    img2.setUnsignedInts();

    vector<Pixel> img1pixels = img1.getPixels();
    vector<Pixel> img2pixels = img2.getPixels();

    vector<Pixel> resultPixels;

    for (unsigned int i = 0; i < img1pixels.size(); i++)
    {
        Pixel resultPixel;

        unsigned int blueInt = (unsigned int)(scale(img1pixels[i].blueint * img2pixels[i].blueint / 255.0f));
        unsigned char blue = img1.IntToChar(blueInt);
        resultPixel.blue = blue;

        unsigned int greenInt = (unsigned int)(scale(img1pixels[i].greenint * img2pixels[i].greenint / 255.0f));
        unsigned char green = img1.IntToChar(greenInt);
        resultPixel.green = green;

        unsigned int redInt = (unsigned int)(scale(img1pixels[i].redint * img2pixels[i].redint / 255.0f));
        unsigned char red = img1.IntToChar(redInt);
        resultPixel.red = red;

        resultPixels.push_back(resultPixel);
    }

    resultImg.setPixels(resultPixels);
    pixels = resultImg.pixels;

    return resultImg;
}

Image Image::Subtract(Image &img1, Image &img2) {
    
    Image resultImg;

    Image::setHeader(img1.getHeader());

    resultImg.setHeader(header);
    img1.setUnsignedInts();
    img2.setUnsignedInts();

    vector<Pixel> img1pixels = img1.getPixels();
    vector<Pixel> img2pixels = img2.getPixels();

    vector<Pixel> resultPixels;

    for (unsigned int i = 0; i < img1pixels.size(); i++)
    {
        Pixel resultPixel;
        int blueInt = img1pixels[i].blueint - img2pixels[i].blueint;
        int greenInt = img1pixels[i].greenint - img2pixels[i].greenint;
        int redInt = img1pixels[i].redint - img2pixels[i].redint;
        
        resultPixel.blueint = (blueInt < 0) ? 0 : ((blueInt > 255) ? 255 : blueInt);
        resultPixel.greenint = (greenInt < 0) ? 0 : ((greenInt > 255) ? 255 : greenInt);
        resultPixel.redint = (redInt < 0) ? 0 : ((redInt > 255) ? 255 : redInt);

        resultPixel.blue = img1.IntToChar(resultPixel.blueint);
        resultPixel.green = img1.IntToChar(resultPixel.greenint);
        resultPixel.red = img1.IntToChar(resultPixel.redint);

        resultPixels.push_back(resultPixel);
    }

    resultImg.setPixels(resultPixels);
    pixels = resultImg.pixels;

    return resultImg;
}
