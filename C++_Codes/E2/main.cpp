#include "my_image.h"
#include <iostream>
using namespace std;
int main(){
    Image image; // image is a ... of struct Image
    initImage(image, 3, 3);
    setPixel(image, {0, 0}, {255, 0, 0});
    setPixel(image, {1, 0}, {0, 255, 0});
    setPixel(image, {2, 0}, {0, 0, 255});
    setPixel(image, {0, 1}, {255, 255, 0});
    setPixel(image, {1, 1}, {255, 0, 255});
    setPixel(image, {2, 1}, {0, 255, 255});
    setPixel(image, {0, 2}, {255, 255, 255});
    setPixel(image, {1, 2}, {0, 0, 0});
    setPixel(image, {2, 2}, {128, 128, 128});
    printImage(image);
    cout << "Image size: " << imageSize(image) << endl;
}