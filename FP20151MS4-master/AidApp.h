#ifndef __244_AIDAPP_H__
#define __244_AIDAPP_H__
#include "Perishable.h"
#include "NFI.h"

namespace oop244{
   class AidApp{
      // private member arguments
      char _filename[256];
      Item* _items[MAX_NO_RECS];
      std::fstream datafile;
      int _noOfItems;


    // copy constructor and assingment operator
    // to prevent copying and assignment
      AidApp(const AidApp&);
      AidApp& operator=(const AidApp&);



    // private member fucntions
      int menu();
      void loadRecs();                        
      void saveRecs();
      void listItems()const;
      int SearchItems(const char* upc)const;
      void updateQty(const char* upc);
      void addItem(bool isPerishable);
    // additional functions
      void deleteItems();

    // sort functions
      void SortByPrice();
      void SortByQuantity();
      void SortByQtyNeeded();
      void SortAlphabetically();
      void displaySortedItems();
    //search function
      int SearchItemsName(const char* name);

      void SearchMenu(bool SearchByName);
  public:
    // constructor and run member function
     AidApp::AidApp(const char* filename);
     int run();


  };
}
#endif
