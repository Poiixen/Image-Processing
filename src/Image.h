#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//REVERSE ORDER (R,G,B) -> (B,G,R)  
struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    
    unsigned int blueint;
    unsigned int greenint;
    unsigned int redint;  
};

class Image {
    public:
        struct Header {
            char idLength;
            char colorMapType;
            char dataTypeCode;
            short colorMapOrigin;
            short colorMapLength;
            char colorMapDepth;
            short xOrigin;
            short yOrigin;
            short width;
            short height;
            char bitsPerPixel;
            char imageDescriptor;
        };
    
        Header getHeader();
        vector<Pixel> getPixels();

        //image properties
        
        void loadImage(string filePath);

        void writeImage(string outName);

        void setUnsignedInts();

        void setHeader(Header headerData);

        void setPixels(vector<Pixel> &vector);

        //
        unsigned int CharToInt(unsigned char character);

        unsigned char IntToChar(unsigned int integer);
        

        float scale(float scale);
        
        unsigned int clamp(int num);
        //


        Image Multiply(Image &A, Image &B);

        Image Subtract(Image &img1, Image &img2);

        Image Screen(Image &img1, Image &img2);

        Image Overlay(Image &img1, Image &img2);

        Image addToGreen(Image &img1, int increment);

        Image scaleRed(Image &img1, int increment1, int increment2);

        Image splitChannels(string rgb, Image &img1);

        Image Combine(Image &img1, Image &img2, Image &img3);

        Image Rotate(Image &img1);

        Image ExtraCredit(Image &img1, Image &img2, Image &img3, Image &img4);

    private:
        Pixel pixel;
        Header header;
        vector<Pixel> pixels;

};