#include <fstream>
#include <iostream>
#include "Image.h"

using namespace std;

float Image::scale(float scale)
{
    scale += 0.5f;
    return scale;
}


vector<Pixel> Image::getPixels()
{
    return pixels;
}

Image::Header Image::getHeader()
{
    return header;
}

unsigned int Image::ConvertCtoI(unsigned char character)
{
    // Converts unsigned char to unsigned int by removing null terminator and type casting
    return (unsigned int)(character - '\0');
}

unsigned char Image::ConvertItoC(unsigned int integer)
{
    // Converts unsigned int to unsigned char by adding null terminator and type casting
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

        pixel.blueint = ConvertCtoI(pixel.blue);
        pixel.greenint = ConvertCtoI(pixel.green);
        pixel.redint = ConvertCtoI(pixel.red);

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

void Image::setUnsignedInts()
{
    for (unsigned int i = 0; i < pixels.size(); i++)
    {
        pixels[i].redint = ConvertCtoI(pixels[i].red);
        pixels[i].greenint = ConvertCtoI(pixels[i].green);
        pixels[i].blueint = ConvertCtoI(pixels[i].blue);
    }
}

void Image::setPixels(vector<Pixel> &vector)
{
    for (unsigned int i = 0; i < vector.size(); i++)
    {
        pixels.push_back(vector[i]);
    }
}

void Image::setHeader(Header &headerData)
{
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

Image Image::Multiply(Image &A, Image &B)
{
    Image C;

    Image::Header header = A.getHeader();
    C.setHeader(header);
    A.setUnsignedInts();
    B.setUnsignedInts();

    vector<Pixel> Apixels = A.getPixels();
    vector<Pixel> Bpixels = B.getPixels();

    vector<Pixel> Cpixels;

    for (unsigned int i = 0; i < Apixels.size(); i++)
    {
        Pixel Cpixel;

        unsigned int redInt = (unsigned int)(scale(Apixels[i].redint * Bpixels[i].redint / 255.0f));
        unsigned char red = A.ConvertItoC(redInt);
        Cpixel.red = red;

        unsigned int greenInt = (unsigned int)(scale(Apixels[i].greenint * Bpixels[i].greenint / 255.0f));
        unsigned char green = A.ConvertItoC(greenInt);
        Cpixel.green = green;

        unsigned int blueInt = (unsigned int)(scale(Apixels[i].blueint * Bpixels[i].blueint / 255.0f));
        unsigned char blue = A.ConvertItoC(blueInt);
        Cpixel.blue = blue;

        Cpixels.push_back(Cpixel);
    }
    C.setPixels(Cpixels);

    return C;
}
