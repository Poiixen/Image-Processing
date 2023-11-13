#include <fstream>
#include <iostream>
#include "Image.h"

using namespace std;

vector<Pixel> Image::getPixels() {
    return pixels;
}

Image::Header Image::getHeader() {
    return header;
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

unsigned int Image::clamp(int num) {
    unsigned int clamp;

    if (num < 0) {
        clamp = 0;
    }
    else if (num > 255) {
        clamp = 255;
    }
    else {
        clamp = num;
    }
    return clamp;
}

float Image::scale(float scale) {
    scale += 0.5f;
    return scale;
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


    for (unsigned int i = 0; i < img1pixels.size(); i++) {
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

    for (unsigned int i = 0; i < img1pixels.size(); i++) {
        Pixel resultPixel;
        int blueInt = img1pixels[i].blueint - img2pixels[i].blueint;
        int greenInt = img1pixels[i].greenint - img2pixels[i].greenint;
        int redInt = img1pixels[i].redint - img2pixels[i].redint;
        
        resultPixel.blueint = clamp(blueInt);
        resultPixel.greenint = clamp(greenInt);
        resultPixel.redint = clamp(redInt);

        resultPixel.blue = img1.IntToChar(resultPixel.blueint);
        resultPixel.green = img1.IntToChar(resultPixel.greenint);
        resultPixel.red = img1.IntToChar(resultPixel.redint);

        resultPixels.push_back(resultPixel);
    }

    resultImg.setPixels(resultPixels);
    pixels = resultImg.pixels;

    return resultImg;
}

Image Image::Screen(Image &img1, Image &img2) {
   
    Image resultImg;
    Image::setHeader(img1.getHeader());

    resultImg.setHeader(header);

    img1.setUnsignedInts();
    img2.setUnsignedInts();

    vector<Pixel> img1Pixels = img1.getPixels();
    vector<Pixel> img2Pixels = img2.getPixels();

    vector<Pixel> resultPixels;

    for (unsigned int i = 0; i < img1Pixels.size(); i++) {
        Pixel resultPixel;

        // Screen blending formula
        int blueInt = 255 - ((255 - img1Pixels[i].blueint) * (255 - img2Pixels[i].blueint) / 255.0f - 0.5f);
        int greenInt = 255 - ((255 - img1Pixels[i].greenint) * (255 - img2Pixels[i].greenint) / 255.0f - 0.5f);
        int redInt = 255 - ((255 - img1Pixels[i].redint) * (255 - img2Pixels[i].redint) / 255.0f - 0.5f);

        resultPixel.blueint = clamp(blueInt);
        resultPixel.greenint = clamp(greenInt);
        resultPixel.redint = clamp(redInt);

        // Convert unsigned ints back to unsigned chars
        resultPixel.blue = img1.IntToChar(resultPixel.blueint);
        resultPixel.green = img1.IntToChar(resultPixel.greenint);
        resultPixel.red = img1.IntToChar(resultPixel.redint);

        resultPixels.push_back(resultPixel);
        
    }

    resultImg.setPixels(resultPixels);
    pixels = resultImg.pixels;
    
    return resultImg;
}

Image Image::Overlay(Image &img1, Image &img2) {
    
    Image resultImg;
    Image::setHeader(img1.getHeader());

    resultImg.setHeader(header);

    img1.setUnsignedInts();
    img2.setUnsignedInts();

    vector<Pixel> img1Pixels = img1.getPixels();
    vector<Pixel> img2Pixels = img2.getPixels();

    vector<Pixel> resultPixels;

    for (unsigned int i = 0; i < img1Pixels.size(); i++)
    {
        Pixel resultPixel;
        unsigned int redInt;
        unsigned int greenInt;
        unsigned int blueInt;

        if (img1Pixels[i].redint <= 127) {
            resultPixel.red  = 0.5f + (2 * (img1Pixels[i].red * img2Pixels[i].red)) / 255.0f;
        }
        else {
            resultPixel.red  = 0.5f + 255 - (2 * (((255 - img1Pixels[i].red) * (255 - img2Pixels[i].red)) / 255.0f));
        }
        
        //________________________________________________________________________//

        if (img1Pixels[i].greenint <= 127) {
            resultPixel.green  = 0.5f + (2 * (img1Pixels[i].green * img2Pixels[i].green)) / 255.0f;
        }
        else {
            resultPixel.green  = 0.5f + 255 - (2 * (((255 - img1Pixels[i].green) * (255 - img2Pixels[i].green)) / 255.0f));
        }

        //________________________________________________________________________//

        if (img1Pixels[i].blueint <= 127) {
            resultPixel.blue  = 0.5f + (2 * (img1Pixels[i].blue * img2Pixels[i].blue)) / 255.0f;
        }
        else {
            resultPixel.blue  = 0.5f + 255 - (2 * (((255 - img1Pixels[i].blue) * (255 - img2Pixels[i].blue)) / 255.0f));
        }
        
        resultPixels.push_back(resultPixel);
    }

    resultImg.setPixels(resultPixels);
    pixels = resultImg.pixels;

    return resultImg;
}

Image Image::addToGreen(Image &img1, int increment) {
    Image resultImg;
    Image::setHeader(img1.getHeader());
    resultImg.setHeader(header);

    for(Pixel& pixel : img1.pixels){
        Pixel resultPixel;
        resultPixel.red = pixel.red;
        resultPixel.green = (pixel.green + increment > 255) ? 255 : pixel.green + increment;
        resultPixel.blue = pixel.blue;
        resultImg.pixels.push_back(resultPixel);
    }

    pixels = resultImg.pixels;
    return resultImg;
}

Image Image::scaleRed(Image &img1, int increment1, int increment2) {
    Image resultImg;
    Image::setHeader(img1.getHeader());
    resultImg.setHeader(header);

    for(Pixel& pixel : img1.pixels){
        Pixel resultPixel;
        resultPixel.red = clamp(pixel.red * increment1);
        resultPixel.green = pixel.green;
        resultPixel.blue = clamp(pixel.blue * increment2);
        resultImg.pixels.push_back(resultPixel);
    }

    pixels = resultImg.pixels;
    return resultImg;
}

Image Image::splitChannels(string rgb, Image &img1)
{
    Image resultImg;
    Image::setHeader(img1.getHeader());

    resultImg.setHeader(header);

    img1.setUnsignedInts();
   
    vector<Pixel> img1Pixels = img1.getPixels();  
    vector<Pixel> resultPixels;

    for (Pixel &img1Pixel : img1Pixels) {
        Pixel resultPixel;
        unsigned char channel;

        if (rgb == "red") {
            channel = img1Pixel.red;
        }
        else if (rgb == "green") {
            channel = img1Pixel.green;
        }
        else if (rgb == "blue") {
            channel = img1Pixel.blue;
        }

        resultPixel.red = channel;
        resultPixel.green = channel;
        resultPixel.blue = channel;

        resultPixels.push_back(resultPixel);
    }

    resultImg.setPixels(resultPixels); 
    pixels = resultImg.pixels;
    
    return resultImg;
}

Image Image::Combine(Image &img1, Image &img2, Image &img3) {
    
    Image resultImg;
    Image::setHeader(img1.getHeader());

    resultImg.setHeader(header);

    img1.setUnsignedInts();
    img2.setUnsignedInts();
    img3.setUnsignedInts();

    vector<Pixel> img1pixels = img1.getPixels();
    vector<Pixel> img2pixels = img2.getPixels();
    vector<Pixel> img3pixels = img3.getPixels();
    
    vector<Pixel> resultPixels;
    
    int size = header.height * header.width;
    
    for (int i = 0; (i < size); i++) {
        Pixel pixel;

        pixel.red = img1pixels.at(i).red;
        pixel.green = img2pixels.at(i).green;
        pixel.blue = img3pixels.at(i).blue;

        resultPixels.push_back(pixel);
    }
    resultImg.setPixels(resultPixels);
    pixels = resultImg.pixels;

    return resultImg;
}

Image Image::Rotate(Image &img1) {

    Image resultImg;
    Image::setHeader(img1.getHeader());

    resultImg.setHeader(header);

    img1.setUnsignedInts();

    vector<Pixel> img1Pixels = img1.getPixels();
    vector<Pixel> resultPixels;

    int height = header.height;
    int width = header.width;

    for (int i = height - 1; i >= 0; i--) {
        for (int j = width - 1; j >= 0; j--) {
            resultPixels.push_back(img1Pixels[i * width + j]);
        }
    }

    resultImg.setPixels(resultPixels);
    pixels = resultImg.pixels;

    return resultImg;
}


Image Image::ExtraCredit(Image &img1, Image &img2, Image &img3, Image &img4) {
    Image newImage;
    newImage.header = img1.header;

    newImage.header.height *= 2;
    newImage.header.width *= 2;

    img1.setUnsignedInts();
    img2.setUnsignedInts();
    img3.setUnsignedInts();
    img4.setUnsignedInts();

    unsigned int img1Index = 0;
    unsigned int img2Index = 0;

    unsigned int half = newImage.header.height / 2;
    unsigned int full = newImage.header.width;

    for (auto i = 0; i < half; i++) {
        for (auto j = 0; j < full; j++) {
            // If j is less than half, we're in the first image
            if (j < half) {
                newImage.pixels.push_back(img1.pixels[img1Index]);
                img1Index++;
            }
            // If j is more than half, we're in the second image
            else {
                newImage.pixels.push_back(img2.pixels[img2Index]);
                img2Index++;
            }
        }
    }

    unsigned int img3Index = 0;
    unsigned int img4Index = 0;

    for (auto i = 0; i < half; i++) {
        for (auto j = 0; j < full; j++) {
            if (j < half) {
                newImage.pixels.push_back(img3.pixels[img3Index]);
                img3Index++;
            }
            else {
                newImage.pixels.push_back(img4.pixels[img4Index]);
                img4Index++;
            }
        }
    }
  
 
    pixels = newImage.pixels;
    return newImage;
}



