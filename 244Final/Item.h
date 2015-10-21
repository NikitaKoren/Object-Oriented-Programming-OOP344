#ifndef __244_ITEM__
#define __244_ITEM__

// header file includes
#include "general.h"
#include "Streamable.h"

namespace oop244{

  class Item :public Streamable{
  private:
     char   _upc[MAX_UPC_LEN + 1]; // holds the UPC (barcode) of the Item
     char*  _name;                 // holds the name 
     double _price;                // Holds the Price 
     bool   _taxed;                // Will be true if this item is taxed
     int    _quantity;             // Holds the on hand (current) quantity
     int    _qtyNeeded;            // Holds the quantity needed for the shipment

     //Allocation and Deallocation of Memory
     void allocate(int size);
     void deallocate();
  public:
    

    // constructors
     Item(const char* upc, const char* name, double price, int qtyNeeded, bool taxed = true);
     Item(const Item& item);           
     Item& operator=(const Item& RO);

    // destructor
     virtual ~Item();

    // setters
     void upc       (const char*);
     void name      (const char*);
     void price     (double);
     void taxed     (bool);
     void quantity  (int);
     void qtyNeeded (int);


    // getters
     const char* upc()  const;
     const char* name() const;
     double price()     const;
     bool   taxed()     const;
     int    quantity()  const;
     int    qtyNeeded() const;
     double cost()      const; // returns the cost of one unit of the the item after tax



    // operators
     bool operator==(const char*) const; // Compare recieved char pointer to UPC
     int operator+=(const int);                // Add the received integer value to the quantity on hand of the Item, returning the sum.


  };
  // Non-member operator overload prototype
  double operator+=(double& d, const Item& I); /* multiplies the cost of the Item by the quantity of the Item  
                                                   then adds that value to the left operand 
                                                    returns the result. */ 
}


#endif