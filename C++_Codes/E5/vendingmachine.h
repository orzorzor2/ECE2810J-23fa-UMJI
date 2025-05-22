#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include <string>

#define MAX_TYPE 10

static std::string food[10] = {"Latte", "Cappuccino", "Americano", "Milk", "Chocolate", "Bread", "Chips",
                               "InstantNoodle", "Biscuit", "Sandwich"};

enum FoodType {
    Latte,
    Cappuccino,
    Americano,
    Milk,
    Chocolate,
    Bread,
    Chips,
    InstantNoodle,
    Biscuit,
    Sandwich,
    Exceed,
};

class Exception {

    std::string message = "";

public:
    Exception(const std::string &message) : message(message) {}

    std::string what() { return message; }
};


class VendingMachine {

protected:
    // the price of each type of food
    int price[MAX_TYPE] = {0};
    // the most delicious type of food existing
    FoodType type;

public:

    /**
     * @brief Default Constructer. Initialize all the price to zero,
     * and set this->type to be the least delicious food.
     */
    VendingMachine();



    /**
     * @brief Set the price of the food for the type given, 
     * and update the most delicious type.
     * @param type 
     * @param price 
     * @throw If the given type is greater or equal to MAX_type, throw an Exception 
     * object with error message "Exceed maximum type!".
     */
    virtual void setPrice(FoodType type, int price);



    /**
     * @brief Get the price of the food for the type given.
     * 
     * @param type 
     * @throw If the given type is more delicious than this->type
     * , throw an Exception object with error message "No food of such type!".
     */
    int getPrice(FoodType type) const;




    /**
     * @brief Print the menu with format "<food type> $<price>\n" to stdout,
     * from the most delicious type to least one, skip all the food with price of zero.
     * Each line represents one type of food.
     * Add a new line after printing the whole menu.
     * @example Sandwich $12
     * @example Chocolate $5
     * @example Latte $1
     */
    virtual void print() const;




    /**
     * @return FoodType, the most delicious food existing
    */
    FoodType getType() const;

    ~VendingMachine() = default;
};

class CoffeeVendor : public VendingMachine {

public:
    /**
     * @brief Default Constructer. Initialize the price of Americano to 1,
     * the price of Latte and Cappuccino to 0,
     * and set this->type to be Americano.
     */
    CoffeeVendor();

    /**
     * @brief Set the price of the coffee for the given type.
     * @param type 
     * @param price 
     * @throw If the given type is not a coffee type, throw an Exception 
     * object with error message "Exceed maximum type!".
     * @throw If the given type is Americano and the given price is 0, throw an Exception
     * object with error message "No Americano!".
     */
    void setPrice(FoodType type, int price);

    /**
     * @brief Print the menu with format "<food type> $<price>\n" to stdout,
     * from the most delicious type to least one, skip all the food with price of zero.
     * Each line represents one type of food.
     * Add a new line after printing the whole menu.
     * @example Sandwich $12
     * @example Chocolate $5
     * @example Latte $1
     */
    void print() const;

    ~CoffeeVendor() = default;

};

#endif // VENDINGMACHINE_H
