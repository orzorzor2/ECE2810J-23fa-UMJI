#ifndef BOX_H
#define BOX_H

#include <iostream>

class Box {
private:
    int *length;
    int *width;
    int *height;
public:
    Box() : length(new int), width(new int), height(new int) {}

    Box(const Box &box) {
        copyFrom(box);
    }                  //重载构造函数
    Box &operator=(const Box &box) {
        if (this != &box) {
            delete length;
            delete width;
            delete height;
            copyFrom(box);
        }
        return *this;
    }

    ~Box() {
        delete length;
        delete width;
        delete height;
    }

    void copyFrom(const Box &box) {
        length = new int;
        width = new int;
        height = new int;
        *length = *box.length;
        *width = *box.width;
        *height = *box.height;
    }

    void set(int l, int w, int h) {
        *length = l;
        *width = w;
        *height = h;
    }

    void show() {
        std::cout << "length address = " << length << std::endl;
        std::cout << "width address = " << width << std::endl;
        std::cout << "height address = " << height << std::endl;
        std::cout << "Length = " << *length << std::endl;
        std::cout << "Width = " << *width << std::endl;
        std::cout << "Height = " << *height << std::endl;
    }
};
#endif // BOX_H