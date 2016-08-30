// Milestone 2
// CustomerOrder.cpp
// Created by Nikita Koren on 24/11/15.
#include "CustomerOrder.h"
#include "Utilities.h"
#include "ItemOrder.h"
#include "Item.h"

#include <vector>
#include <iomanip>

#include <string.h>


// declaring a static member variables
char CustomerOrder::delimiter = '\0';
size_t CustomerOrder::field_width = 1;



CustomerOrder::CustomerOrder(const std::string& record) {

    name    = "";
    product = "";
    order   = nullptr;
    nOrders = 0;


    bool more = true;
    size_t next_pos = 0;
    Utilities utility(field_width);

    //read tokens
    name = utility.nextToken(record, next_pos, more);
    if(more)
        product =  utility.nextToken(record, next_pos, more);

    //vector to store products that customer wants to order
    std::vector<std::string> orders_vec;
    std::string temp_record;
    while(more) {
        temp_record = "";
        temp_record = utility.nextToken(record, next_pos, more);
        if(!temp_record.empty()) {
            orders_vec.push_back(temp_record);
            nOrders++;
        }
    }

    order = new ItemOrder[nOrders];

    for(size_t i = 0; i < nOrders; i++)
        order[i] = ItemOrder(orders_vec[i]);


    //if (utility.getFieldWidth() < field_width)
        field_width = utility.getFieldWidth();

}


//CustomerOrder::CustomerOrder(const CustomerOrder& rhs_order) {
// throw std::string("the copy constructor should never be called");
//}


CustomerOrder::CustomerOrder(CustomerOrder&& rhs) {
    *this = std::move(rhs);
}


CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& rhs) {

    if (this != &rhs) {

        //copy
        name      = rhs.name;
        product   = rhs.product;
        nOrders   = rhs.nOrders;
        order     = rhs.order;
        delimiter = rhs.delimiter;
        field_width = rhs.field_width;

        //delete
        rhs.name    = "";
        rhs.product = "";
        rhs.nOrders = 0;
        rhs.order   = nullptr;
        rhs.delimiter   = '\0';
        rhs.field_width = 0;

    }
    return std::move(*this);
}


CustomerOrder::~CustomerOrder() {
    if (order)
        delete [] order;
}


unsigned int CustomerOrder::noOrders() const {
    return nOrders;
}


const std::string&  CustomerOrder::operator[](unsigned int i) const {

    if(i > nOrders) {
        throw std::string("the index is out of bounds");
    }

    return order[i].getName();
}

void CustomerOrder::fill(Item& item) {
    for (int i = 0; i < nOrders; i++) {
        if (!order[i].getName().compare(item.getName())) {
            order[i].fill(item.getCode());
            item++;
        }
    }
}

void CustomerOrder::remove(Item& item) {
    for (int i = 0; i < nOrders; i++) {
        if (!order[i].getName().compare(item.getName()))
            order[i].clear();
    }
}


bool CustomerOrder::empty() const {
    return name.empty();
}

void CustomerOrder::setDelimiter(const char c) {
    delimiter = c;
}

void CustomerOrder::display(std::ostream& os) const {

    os << std::left << std::setw(field_width) << name << " : ";

    os << std::setw(field_width) << product << std::endl;

    for (int i = 0; i < nOrders; i++)
        order[i].display(os);
}







