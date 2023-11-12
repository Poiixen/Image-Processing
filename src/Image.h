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

        void setHeader(Header &headerData);

        void setPixels(vector<Pixel> &vector);

        bool operator==(Image &other);

        //

        unsigned int ConvertCtoI(unsigned char character);

        unsigned char ConvertItoC(unsigned int integer);

        //


        Image Multiply(Image &A, Image &B);

        void Subtract(Image &img1, Image &img2);

        void Screen(Image &img1, Image &img2);

        void Overlay(Image &img1, Image &img2);

        void scaleGreen(Image &img1);

        void scaleRed(Image &img1);

        void splitChannels(string rgb, Image &img1);

        void Combine(Image &img1, Image &img2, Image &img3);

        void Rotate(Image &img1);

        float scale(float scale);

    private:
        Pixel pixel;
        Header header;
        vector<Pixel> pixels;

};



    