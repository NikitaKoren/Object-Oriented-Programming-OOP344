#pragma once
// CustomerOrder Milestone - Item Interface
// Item.h
// Chris Szalwinski
// v1.0 - 9/11/2015
#include <iostream>
#include <string>

class Item {
    std::string name;
    std::string source;
    std::string destination;
    std::string details;
    unsigned int code;
    static char delimiter;
    static size_t field_width;
public:

    /*
     * The constructor initializes the description string to "no detailed description" and code to the default initial
     * code (1) for all items.  The constructor extracts tokens from the string received using a Utilities object.
     * It accepts the first token as the name of the item and reports an exception if no name is specified.
     * It accepts the second token as the name of the source task that inserts the item into a product and reports
     * an exception if no task is specified.  It accepts the third token as the destination task that extracts the item
     * from a product and reports an exception if no task is specified.  The fourth token is the integer holding
     * the code to be printed on the item's first insertion.  The fifth token is a detailed description of the item.
     * The constructor resets the field_width of the Item class if the size of the item name exceeds
     * the current field_width.
     * */

    Item(const std::string& = std::string());

    // returns true if the current object is in a safe empty state
    bool empty() const;

    // increments the code to be printed on the next insertion by 1
    void operator++(int);

    // returns a copy of the code to be printed on the next insertion
    unsigned int getCode() const;

    // returns a copy of the string that contains the name of the item
    const std::string& getName() const;

    // returns a copy of the string that contains the name of the task that inserts the item into a product
    const std::string& getSource() const;

    // returns a copy of the string that contains the name of the task that extracts the item from a product
    const std::string& getDestination() const;

    // reset the delimiter for all Itemobjects to the character received
    static void setDelimiter(const char);

    // returns the field_width for all Item objects processed
    static size_t getFieldWidth();


    void display(std::ostream&, bool = false) const;

};