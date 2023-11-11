#include <iostream>
#include <vector>
#include <string>
#include "Image.h"

using namespace std;

bool comparePixels(Image &img1, Image &img2) {

   vector<Pixel> pixels1 = img1.getPixels();
    vector<Pixel> pixels2 = img2.getPixels();
    for (int i = 0; i < pixels1.size(); i++) {
        if ((int)pixels1.at(i).red != (int)pixels2.at(i).red)
            return false;
        if ((int)pixels1.at(i).green != (int)pixels2.at(i).green)
            return false;
        if ((int)pixels1.at(i).blue != (int)pixels2.at(i).blue)
            return false;
    }
    return true;
}

/* bool compareHeader(const Image &img1, const Image& img2) {
    const auto& header1 = img1.getHeader();
    const auto& header2 = img2.getHeader();

    for (const auto& field : {
            &Header::idLength, &Header::colorMapType, &Header::dataTypeCode,
            &Header::colorMapOrigin, &Header::colorMapLength, &Header::colorMapDepth,
            &Header::xOrigin, &Header::yOrigin, &Header::width, &Header::height,
            &Header::bitsPerPixel, &Header::imageDescriptor
        }) {
        if (*field(header1) != *field(header2)) {
            return false;
        }
    }

    // If all fields are equal, return true
    return true;
}
*/

int Test(Image img1, Image img2, int testNum) {
        
    if (comparePixels(img1, img2)) { //&& compareHeaders(img1, img2)) {   //TODO: COMPARISON CHECKS
        cout << "Test " << testNum << ".....Passed" << endl;
        return 1;
    }
    else {
        cout << "Test " << testNum << ".....Failed" << endl;
        return 0;
    }
};


int main() {
    
    int passedTests = 0;
    int totalTests = 12;

    // loading my images

    Image car;
    Image circles;
    Image layer_blue;
    Image layer_green;
    Image layer_red;
    Image layer1;
    Image layer2;
    Image pattern1;
    Image pattern2;
    Image text;
    Image text2;

    car.loadImage("./input/car.tga");
    circles.loadImage("./input/circles.tga"); 
    layer_blue.loadImage("./input/layer_blue.tga");
    layer_green.loadImage("./input/layer_green.tga");
    layer_red.loadImage("./input/layer_red.tga");
    layer1.loadImage("./input/layer1.tga");
    layer2.loadImage("./input/layer2.tga");
    pattern1.loadImage("./input/pattern1.tga");
    pattern2.loadImage("./input/pattern2.tga");
    text.loadImage("./input/text.tga");
    text2.loadImage("./input/text2.tga");
    
    
    // loading examples for comparison

    Image EXAMPLE_part1;
    Image EXAMPLE_part2;
    Image EXAMPLE_part3;
    Image EXAMPLE_part4;
    Image EXAMPLE_part5;
    Image EXAMPLE_part6;
    Image EXAMPLE_part7;
    Image EXAMPLE_part8_b;
    Image EXAMPLE_part8_g;
    Image EXAMPLE_part8_r;
    Image EXAMPLE_part9;
    Image EXAMPLE_part10;
    Image EXAMPLE_extracredit;

    EXAMPLE_part1.loadImage("./examples/EXAMPLE_part1.tga");
    EXAMPLE_part2.loadImage("./examples/EXAMPLE_part2.tga");
    EXAMPLE_part3.loadImage("./examples/EXAMPLE_part3.tga");
    EXAMPLE_part4.loadImage("./examples/EXAMPLE_part4.tga");
    EXAMPLE_part5.loadImage("./examples/EXAMPLE_part5.tga");
    EXAMPLE_part6.loadImage("./examples/EXAMPLE_part6.tga");
    EXAMPLE_part7.loadImage("./examples/EXAMPLE_part7.tga");
    EXAMPLE_part8_r.loadImage("./examples/EXAMPLE_part8_r.tga");
    EXAMPLE_part8_g.loadImage("./examples/EXAMPLE_part8_g.tga");
    EXAMPLE_part8_b.loadImage("./examples/EXAMPLE_part8_b.tga");
    EXAMPLE_part9.loadImage("./examples/EXAMPLE_part9.tga");
    EXAMPLE_part10.loadImage("./examples/EXAMPLE_part10.tga");
    EXAMPLE_extracredit.loadImage("./examples/EXAMPLE_extracredit.tga");

    
    
    Image part1 = Multiply(layer1, pattern1);

    passedTests += Test(part1, EXAMPLE_part1, 1);
    
    
    return 0;
};


/*
    void ExtraCredit() {
        //TODO: implement
    }
*/
