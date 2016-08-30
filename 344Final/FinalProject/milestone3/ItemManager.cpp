// ItemManager.cpp
// Created by Nikita Koren on 01/12/15.
//

#include "ItemManager.h"
#include "Item.h"

void ItemManager::push_back(Item&& item) {
    return items.push_back(std::move(item));
}

std::vector<Item>::iterator ItemManager::begin() {
    return items.begin();
}

std::vector<Item>::iterator ItemManager::end() {
    return items.end();
}

const std::vector<Item>::const_iterator ItemManager::cbegin() const {
    return items.cbegin();
}

const std::vector<Item>::const_iterator ItemManager::cend() const {
    return items.cend();
}

void ItemManager::display(std::ostream& os, bool full) const {

    for(int i = 0; i < items.size(); i++)
        items[i].display(os, full);
}