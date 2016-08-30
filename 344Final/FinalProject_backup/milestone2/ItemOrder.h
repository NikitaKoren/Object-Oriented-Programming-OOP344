#pragma once
// CustomerOrder Milestone 2 - ItemOrder Interface
// ItemOrder.h
// Chris Szalwinski
// v1.0 - 9/11/2015
#include <iostream>
#include <string>

class Item;

class ItemOrder {
    std::string name;
    bool filled;
    unsigned int code;
public:

    /*
     * The constructor initializes the name identifying the item ordered to the name received or to an empty state if
     * no name was received, initializes filled to false and initializes the item code to 0.
     * */
    ItemOrder(const std::string& = std::string());

    // returns true if the current order asks for item; false otherwise
    bool asksFor(const Item&) const;

    // returns true if the current order has been filled
    bool isFilled() const;

    //  sets the item code for the current object to the value received and switches the status of the current object to filled
    void fill(const unsigned int);

    //  resets the item code for the current object to 0 and resets the status of the current object to not filled
    void clear();

    // returns name of a class
    const std::string& getName() const;

    void display(std::ostream&) const;
};