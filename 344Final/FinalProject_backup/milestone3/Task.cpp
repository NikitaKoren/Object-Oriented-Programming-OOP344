// Milestone 1
// Task.cpp
// Created by Nikita Koren on 22/11/15.

#include "Task.h"
#include "Utilities.h"
#include <iomanip>

// declaring a static member variables
char Task::delimiter = '\0';
size_t Task::field_width = 1;


Task::Task(const std::string &record) : name(""), slots("1"){

    //std::cout << "in Task Record:    "<<record << std::endl;
    //set the next tasks to safe addresses
    nextTask [passed]    = "";
    nextTask [redirect]  = "";
    pNextTask[passed]    = nullptr;
    pNextTask[redirect]  = nullptr;

    /* The Task object uses a Utilities constructor to extract each token from the record */

    //create utility object with a default size
    Utilities utility(field_width);

    // more will be true if the function(nextToken) finds more tokens after the extracted token; otherwise, false
    bool more = true;
    size_t next_pos = 0;

    std::string token = "";

    /* read tokens (all data until delimiter(|)) into variables in the Task Class
     * 1. name
     * 2. slot
     * 3. passedTask
     * 4. redirectTask
     * */

    name = utility.nextToken(record, next_pos, more);

    if(more)
        slots = utility.nextToken(record, next_pos, more);
    if(more)
        nextTask[passed] = utility.nextToken(record, next_pos, more);
    if(more)
        nextTask[redirect] = utility.nextToken(record, next_pos, more);

    if (utility.getFieldWidth() < field_width)
        field_width = utility.getFieldWidth();


   // std::cout << "record: " << name << ", " << slots << ", " << nextTask[passed] << ", " << nextTask[redirect] << std::endl;

}


const std::string& Task::getName() const{
    return name;
}

unsigned int Task::getSlots() const {
    return std::stoi(slots);
}

bool Task::validate(const Task& task) {

    bool error = false;

    if(nextTask[passed].compare(task.name)) {
        pNextTask[passed] = &task;
        error = true;
    }

    if(nextTask[redirect].compare(task.name)) {
        pNextTask[redirect] = &task;
        error = true;
    }

    return error;
}

const Task* Task::getNextTask(Quality quality) const {

    if (!pNextTask[quality])
        throw std::string("*** Validate  [") + nextTask[quality] + std::string("] @ [") + name + std::string("] ***");

    return pNextTask[quality];

}

void Task::display(std::ostream& os) const {


    os << "Task Name    : " << std::left << std::setw(field_width+15) << (std::string("[") + name + std::string("]")) << std::setw(2) << " " <<"[" << slots << "]";
    os << std::endl;  

    if (!nextTask[passed].empty()) {
        os << " Continue to : " << std::setw(field_width+16) << (std::string("[") + nextTask[passed] + std::string("]"));
        if (!pNextTask[passed])
            os << " *** to be validated ***";

        os<< std::endl;
    }

    if (!nextTask[redirect].empty()) {
        os << " Redirect to : " << std::setw(field_width+16) << (std::string("[") + nextTask[redirect] + std::string("]"));
        if (!pNextTask[redirect])
            os << " *** to be validated ***";

        os << std::endl;
    }


}

void Task::setDelimiter(const char c) {
    delimiter = c;
}

size_t Task::getFieldWidth() {
    return field_width;
}

bool operator==(const Task& lTask, const Task& rTask) {

    // returns true if the tasks referenced in its parameters have the same name */
    if (lTask.getName().compare(rTask.getName()))
        return true;
    else
        return false;
}
