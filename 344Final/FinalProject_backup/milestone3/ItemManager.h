#pragma once
// Manager Milestone - ItemManager Interface
// ItemManager.h
// Chris Szalwinski
// v1.0 - 16/11/2015
#include <iostream>
#include <vector>


class Item;

class ItemManager {
    std::vector<Item> items;
public:
    //  moves item to the back of items
    void push_back(Item&&);

    //  returns the iterator to the beginning of items
    std::vector<Item>::iterator begin();

    // returns the iterator to the end of items
    std::vector<Item>::iterator end();

    //  returns the iterator to the beginning of read-only items
    const std::vector<Item>::const_iterator cbegin() const;

    //  returns the iterator to the end of read-only items
    const std::vector<Item>::const_iterator cend() const;

    // inserts into the referenced ostream object descriptions of the items stored in items
    void display(std::ostream&, bool = false) const;
};