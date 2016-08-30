// TaskManager.cpp
// Created by Nikita Koren on 06/12/15.
//

#include "Task.h"
#include "Item.h"
#include "ItemManager.h"
#include "TaskManager.h"

#include <algorithm>


void TaskManager::push_back(Task&& task) {
    tasks.push_back(std::move(task));
}

std::vector<Task>::iterator TaskManager::begin () {
    return tasks.begin();
}

std::vector<Task>::iterator TaskManager::end() {
    return tasks.end();
}

const std::vector<Task>::const_iterator TaskManager::cbegin() const {
    return tasks.cbegin();
}

const std::vector<Task>::const_iterator TaskManager::cend() const {
    return tasks.cend();
}

void TaskManager::validate(std::ostream& os) {

    bool valid = true;
    for (auto i = 0u; i < tasks.size() && valid; i++) {

        bool invalid = true;
        for (auto j = 0u; j < tasks.size() && invalid; j++) {
            if (tasks[i].validate(tasks[j]))
                invalid = false;
        }
        valid = !invalid;
    }
    if (!valid)
        os << "*** Not all Tasks have been validated ***\n";
}

void TaskManager::display(std::ostream& os) const {
    for(int i = 0; i < tasks.size(); i++)
        tasks[i].display(os);
}


void validate(const TaskManager& task, const ItemManager& item, std::ostream& os){

    auto avaliable = [&](const Item& items){

        bool valid = false;
        for (auto it = task.cbegin(); it != task.cend(); it++){
            
            if (items.getDestination() == it->getName())
                valid = true;

        }

        if (!valid)
            os << items.getDestination()<< " is unavailable!"<< std::endl;

        return false;
    };
    
    std::find_if(item.cbegin(),item.cend(),avaliable);
}