#ifndef _VENDINGMACHINE_H
#define _VENDINGMACHINE_H
#include <string>

#define MAX_TYPE 10

static std::string food[10] = {"Latte", "Cappuccino", "Americano", "Milk", "Chocolate"
        , "Bread", "Chips", "InstantNoodle", "Biscuit", "Sandwich"};

enum FoodType{
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

class Exception{

    std::string message="";

public:
    Exception(const std::string & message): message(message) {}
    std::string what() {return message;}
};

class VendingMachine {

protected:
    // dynamic array of the price
    int *price;
    // true if no food exists
    bool empty;
    // the most delicious type of food existing
    FoodType type;

public:

    /**
     * @brief Default Constructer. Initialize all the price to zero,
     * and set this->type to be the least delicious food.
     */
    VendingMachine();

    /**
    * @brief Overloaded Constructer. Initialize a vending machine with one type of food.
    * @param type
    * @param price
    * @throw If the given degree is greater or equal to MAX_TYPE, throw an
    * Exception object with error message "Exceed maximum type!".
    */
    VendingMachine(FoodType type, int price);

    /**
     * @brief Set the price of the food for the type given,
     * and update the most delicious type.
     * @param type
     * @param price
     * @throw If the given type is greater or equal to MAX_TYPE, throw an Exception
     * object with error message "Exceed maximum type!".
     */
    virtual void setPrice(FoodType type,int price);

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

    bool isEmpty() const;

    void setEmpty(bool empty) { this->empty = empty; };

    void setType(FoodType type) { this->type = type; };


    /**
    * @brief Check the invariants of the class
    * return whether the invariants of class are correct.
    */
    bool repOK();

    /**
    * @brief Default Destructer.
    * Release memory of price.
    */
    ~VendingMachine();

};


#endif // _VENDINGMACHINE_H
