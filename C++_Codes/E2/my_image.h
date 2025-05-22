#ifndef UNTITLED_MY_IMAGE_H
#define UNTITLED_MY_IMAGE_H

#include "cstddef"

const size_t MAX_WIDTH = 64;
const size_t MAX_HEIGHT = 64;

//Alias unsigned char to channel
typedef unsigned char Channel;

//Represent the position of the pixel
struct Vec2 {
    size_t _x;
    size_t _y;
};

//store the RGB information of a pixel
struct Pixel {
    Channel _red;
    Channel _green;
    Channel _blue;
};

//Information of the whole image
struct Image {
    size_t _width;
    size_t _height;
    Pixel _pixels[MAX_WIDTH * MAX_HEIGHT];
};

//Function declarations

void initImage(Image &image, size_t width, size_t height);

void setPixel(Image &image, const Vec2 &pos, const Pixel &pixel);

size_t imageSize(Image &image);


void printImage(Image &image, bool decOut = false);//这样不说就是false，写明了true就是true


#endif //UNTITLED_MY_IMAGE_H
