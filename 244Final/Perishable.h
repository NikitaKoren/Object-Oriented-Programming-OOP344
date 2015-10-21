#ifndef __244_erishable_H__
#define __244_Perishable_H__
// includes go here
#include "Item.h"
#include "ErrorMessage.h"
#include <cstring>
#include "Date.h"

namespace oop244{
  class Perishable:public Item{
  private:
    ErrorMessage _err;
    char _unit[11];
    // expiry and unit go here
    Date _expiry;
  public:
    // default constructor
     Perishable();
    // pure virutal method implementation prototypes
     std::fstream& store(std::fstream& file)const;
     std::fstream& load(std::fstream& file);
     std::ostream& display(std::ostream& os, bool linear = true)const;
     std::istream& conInput(std::istream& is);


    // Setters and Getters
     const Date& expiry()const;
     void expiry(const Date &value);

     const char* unit()const;
     void unit(const char* value);

     ~Perishable();

  };
}


#endif
