#pragma once
// CustomerOrder Milestone 2 - CustomerOrder Interface
// CustomerOrder.h
// Chris Szalwinski
// v1.0 9/11/2015
#include <iostream>
#include <string>

class Item;
class ItemOrder;

class CustomerOrder {
    std::string name;
    std::string product;
    ItemOrder* order;
    unsigned int nOrders;
    static char delimiter;
    static size_t field_width;
public:


    /*
     *  The constructor initializes the number of orders to 0 and the pointer to the ItemOrder array to a safe address.
     * The constructor uses a Utilities object to determine the number of tokens in the referenced string.
     * The constructor reports appropriate exceptions if the record the customer name field, the product name field,
     * or any item field.  The constructor allocates dynamic memory for the ItemOrders identified in the referenced
     * string.  It stores the name of the customer, stores the name of the product and populates the ItemOrder array.
     * Finally, the constructor extracts the field width from the Utilities object and updates the field_width class
     * variable if that field width is greater than the class variable's current value.  Once all customer orders
     * have been processed, this class variable holds the field width required to display their names in aligned
     * tabular form.
     * */
    CustomerOrder(const std::string&);


    /* the copy constructor should never be called.  Your implementation reports an exception if the copy constructor is called. */
    CustomerOrder(const CustomerOrder&) = delete;


    CustomerOrder& operator=(const CustomerOrder&) = delete;


    //move semantics
    CustomerOrder(CustomerOrder&&);
    CustomerOrder&& operator=(CustomerOrder&&);

    ~CustomerOrder();

    // returns the number of item orders in the current object
    unsigned int noOrders() const;


    // returns a reference to the name of item order i; reports an exception if the index is out of bounds
    const std::string& operator[](unsigned int i) const;


    /*
     * searches through the ordered items and fills those orders identified by the name of the Item received
     * if any have not been filled.  This function increments the Item object's code for each order filled
     * */
    void fill(Item&);


    /*
     * searches through the items ordered and removes those items identified by the name of the Item received
     * if the corresponding order has been filled.  This function does not alter the Item object's code
     * */
    void remove(Item&);


    // returns true if the current object is in a safe empty state
    bool empty() const;


    /* Display:
     * - the name of the customer left-justified in a field of width field_width
     * - the name of the product left-justified in a field of width field_width
     * - each item ordered on a separate line
     * */
    void display(std::ostream&) const;

    //  resets the delimiter for extracting tokens to the character received
    static void setDelimiter(const char);

};

