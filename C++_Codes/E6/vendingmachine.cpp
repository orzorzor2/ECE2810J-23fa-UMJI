#include "vendingmachine.h"
#include <iostream>


//price = new int[MAX_TYPE]


VendingMachine::VendingMachine() : price(new int[MAX_TYPE]), empty(true), type(Latte) {
    for (int i = 0; i < MAX_TYPE; i++) {
        price[i] = 0;
    }
}

//重载可以不用初始化列表吗，在主题中定义动态数组
VendingMachine::VendingMachine(FoodType type, int price) : price(new int[MAX_TYPE]), empty(true), type(type) {
    // 检查type是否合法，如果不合法，抛出异常
    if (type >= MAX_TYPE || type == Exceed) {
        throw Exception("Exceed maximum type!");
    }
    for (int i = 0; i < MAX_TYPE; i++) {
        this->price[i] = 0;
    }
    // 把给定的type对应的元素设置为给定的price
    this->price[type] = price;
    // 设置type为给定的type
    // 设置empty为false，表示有食物存在
    if (price != 0) {
        this->empty = false;
    }
}


void VendingMachine::setPrice(FoodType type, int price) {
    if (type >= MAX_TYPE || type == Exceed) {
        throw Exception("Exceed maximum type!");
    }
    this->price[type] = price;
    this->type = type; //type 成员就是most delicious type
    this->empty = this->isEmpty();//   !!!
}

int VendingMachine::getPrice(FoodType type) const {
    if (type > this->type) {
        throw Exception("No food of such type!");
    }
    return this->price[type];
}

void VendingMachine::print() const {
    for (int i = MAX_TYPE - 1; i >= 0; i--) {
        if (this->price[i] != 0) {
            std::cout << food[i] << " $" << this->price[i] << std::endl;
        }
    }
    std::cout << std::endl;
}

FoodType VendingMachine::getType() const {
    return this->type;
}

bool VendingMachine::isEmpty() const {
    for (int i = 0; i < MAX_TYPE; i++) {
        if (this->price[i] != 0) {
            return false;
        }
    }
    return true;
}


bool VendingMachine::repOK()
{
    int itemCount = 0; // Better variable name for clarity
    for(int i = 0; i < MAX_TYPE; i++) {
        // Check for item price and machine emptiness
        if(this->price[i] == 0) itemCount++;
        if(this->price[i] != 0 && this->empty == true) return false;
    }
    // Check for consistency in item count and emptiness
    if(itemCount == 10 && this->empty == false) return false;
    // If the machine type is Sandwich and any price is non-zero, return false
    if(this->type == Sandwich) {
        for(int j = 0; j < MAX_TYPE; j++) {
            if(this->price[j] != 0) return false;
        }
    }
    return true;
}


VendingMachine::~VendingMachine() {
    delete[] price;
}