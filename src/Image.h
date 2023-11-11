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
        
        void loadImage(string filePath);

        void writeImage(string outName);

        void setUnsignedInts();

        void setHeader(Header &headerData);

        void setPixelVector(vector<Pixel> &vector);

        bool operator==(Image &other);

    private:
        Pixel pixel;
        Header header;
        vector<Pixel> pixels;

};