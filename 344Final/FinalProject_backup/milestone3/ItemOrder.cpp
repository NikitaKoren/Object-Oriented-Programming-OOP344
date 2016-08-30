// Created by Nikita Koren on 24/11/15.

#include "ItemOrder.h"
#include "Utilities.h"
#include "Item.h"
#include <iomanip>

ItemOrder::ItemOrder(const std::string& str) {

    name   = str;
    filled = false;
    code   = 0;
}

bool ItemOrder::asksFor(const Item& item) const {

    if( name == item.getName())
        return true;
    else
        return false;
}

bool ItemOrder::isFilled() const {

    return filled;
}

void ItemOrder::fill(const unsigned int c) {
    code = c;
    filled = true;
}

void ItemOrder::clear() {
    code = 0;
    filled = false;
}

const std::string& ItemOrder::getName() const {
    return name;
}

void ItemOrder::display(std::ostream& os) const {

    if (name.size() > 0) {
        os << " " << (filled ? "+" : "-");
        os << " [" << std::right << std::setw(CODE_WIDTH) << std::setfill('0') << code << std::setfill(' ') << "] ";
        os << name << std::endl;
    }
}
