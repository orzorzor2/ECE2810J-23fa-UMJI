#include <iostream>
#include "my_image.h"
#include "cstddef"

//Initialize image with given parameters of height and width, and set all pixels to (0, 0, 0)
void initImage(Image& image, size_t width, size_t height) {
    image._height = height;
    image._width = width;
    for (size_t i = 0; i < width * height; i++) {
        image._pixels[i]._red = 0;
        image._pixels[i]._green = 0;
        image._pixels[i]._blue = 0;
    }
}

//set the color of the pixel at a given position (_x, _y)
void setPixel(Image& image, const Vec2 &pos, const Pixel &pixel) {
    if ((pos._x < 0) || (image._width <= pos._x) || (image._height <= pos._y) || (pos._y < 0)) {
        std::cout << "Error: pixel out of range!" << std::endl;
        return;
    }
    size_t index = pos._y * image._width + pos._x;
    image._pixels[index] = pixel;

}
//return the number of image size
size_t imageSize(Image& image) {
    return image._height * image._width;
}

//print out all the image in desired format
void printImage(Image& image, bool decOut) {
    if (!decOut) {
        for (size_t i = 0; i < image._height; i++) {
            for (size_t j = 0; j < image._width; j++) {
                std::cout << "(" << static_cast<int>(image._pixels[i * image._width + j]._red) << ","
                          << static_cast<int>(image._pixels[i * image._width + j]._green) << ","
                          << static_cast<int>(image._pixels[i * image._width + j]._blue) << ")"; //加了&不知道
            }
            std::cout << " " << std::endl;
        }
    } else {
        for (size_t i = 0; i < image._height; i++) {
            for (size_t j = 0; j < image._width; j++) {
                std::cout << "(" << static_cast<double>(image._pixels[i * image._width + j]._red) / 255 << ","
                          << static_cast<double>(image._pixels[i * image._width + j]._green) / 255 << ","
                          << static_cast<double>(image._pixels[i * image._width + j]._blue) / 255 << ")"; //加了&不知道
            }
            std::cout << " " << std::endl;
        }
    }
}