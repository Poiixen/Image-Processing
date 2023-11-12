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


bool compareHeaders(Image img1, Image img2) {
    if ((int)img1.getHeader().idLength != (int)img2.getHeader().idLength)
        return false;
    if ((int)img1.getHeader().colorMapType != (int)img2.getHeader().colorMapType)
        return false;
    if ((int)img1.getHeader().dataTypeCode != (int)img2.getHeader().dataTypeCode)
        return false;
    if ((short)img1.getHeader().colorMapOrigin != (short)img2.getHeader().colorMapOrigin)
        return false;
    if ((short)img1.getHeader().colorMapLength != (short)img2.getHeader().colorMapLength)
        return false;
    if ((int)img1.getHeader().colorMapDepth != (int)img2.getHeader().colorMapDepth)
        return false;
    if ((short)img1.getHeader().xOrigin != (short)img2.getHeader().xOrigin)
        return false;
    if ((short)img1.getHeader().yOrigin != (short)img2.getHeader().yOrigin)
        return false;
    if ((short)img1.getHeader().width != (short)img2.getHeader().width)
        return false;
    if ((short)img1.getHeader().height != (short)img2.getHeader().height)
        return false;
    if ((int)img1.getHeader().bitsPerPixel != (int)img2.getHeader().bitsPerPixel)
        return false;
    if ((int)img1.getHeader().imageDescriptor != (int)img2.getHeader().imageDescriptor)
        return false;
    return true;
}

int Test(Image img1, Image img2, int testNum) {
        
    if (comparePixels(img1, img2) && compareHeaders(img1, img2)) {   //TODO: COMPARISON CHECKS
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

   
//Test1:
  
    Image part1;
    part1.Multiply(layer1, pattern1);
    part1.writeImage("output/part1.tga");
    passedTests += Test(part1, EXAMPLE_part1, 1);



/*
Test2:

    Image part2; 
    part2.Subtract(car, layer2);
    part2.writeImage("output/part2.tga")
    passedTests += Test(part2, EXAMPLE_part2, 2);
    
Test3:

    Image temp;
    temp.Multiply(layer1, pattern2);
    
    Image part3;
    part3.Screen(text, temp);

    part3.writeImage("output/part3.tga")
    passedTests += Test(part3, EXAMPLE_part3, 3);

Test4:

    Image temp2;
    temp2.Multiply(layer2, circles);
    
    Image part4;
    part4.Subtract(temp2, pattern2);
    part4.writeImage("output/part4.tga");
    passedTests += Test(part4, EXAMPLE_part4, 4);

Test5:

    Image part5;
    part5.Overlay(pattern1, layer1);
    part5.writeImage("output/part5.tga");
    passedTests += Test(part5, EXAMPLE_part5, 5);

Test6:
    
    Image part6;
    part6.addGreen(car);
    part6.writeImage("output/part6.tga");
    passedTests += Test(part6, EXAMPLE_part6, 6);


Test7:

    Image part7;
    part7.scaleRed(car);
    part7.WriteImage("output/part7.tga");
    passedTests += Test(part7, EXAMPLE_part7, 7);

Test8:
    
    Image part8_blue;
    part8_blue.splitChannels("blue", car);
    
    Image part8_green;
    part8_green.splitChannels("green", car);

    Image part8_red;
    part8_red.splitChannels("red", car);
   

    part8_blue.writeImage("output/part8_b.tga");
    part8_green.writeImage("output/part8_g.tga");
    part8_red.writeImage("output/part8_r.tga");

    passedTests += Test(part8_blue, EXAMPLE_part8_b);
    passedTests += Test(part8_green, EXAMPLE_part8_g);
    passedTests += Test(part8_red, EXAMPLE_part8_r);

Test9:

    Image part9;
    part9.Combine(layer_red, layer_green, layer_blue);
    part9.writeImage("output/part9.tga");
    passedTests += Test(part9, EXAMPLE_part9, 9);


Test10:

    Image part10;
    part10.Rotate(text2);
    part10.writeImage("output/part9.tga")
    passedTests += Test(part10, EXAMPLE_part10, 10);
    
*/
    

    cout << "Total tests passed: " << passedTests << "/10";

    return 0;
};


/*
    void ExtraCredit() {
        //TODO: implement
    }
*/
