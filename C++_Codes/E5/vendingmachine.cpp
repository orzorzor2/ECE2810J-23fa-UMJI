#include "vendingmachine.h"
#include <iostream>

VendingMachine::VendingMachine() : price{0}, type(Latte) {}

void VendingMachine::setPrice(FoodType type, int price) {
    if (type >= MAX_TYPE - 1 || type == Exceed) {
        throw Exception("Exceed maximum type!");
    }
    this->price[type] = price;
    this->type = type; //type 成员就是most delicious type
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

CoffeeVendor::CoffeeVendor() {
    this->price[Americano] = 1;
    this->price[Cappuccino] = 0;
    this->price[Latte] = 0;
    this->type = Americano;
}

void CoffeeVendor::setPrice(FoodType type, int price) {
    if (type > Americano) {
        throw Exception("Exceed maximum type!");
    }
    if (type == Americano && price == 0) {
        throw Exception("No Americano!");
    }
    this->price[type] = price;
    this->type = type;
}

void CoffeeVendor::print() const {
    for (int i = Americano; i >= 0; i--) {
        if (this->price[i] != 0) {
            std::cout << food[i] << " $" << this->price[i] << std::endl;
        }
    }
    std::cout << std::endl;
}
