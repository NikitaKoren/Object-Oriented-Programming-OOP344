#include <cstring>
#include <new>
#include <iomanip>
#include "AidApp.h"
#include <fstream>


using namespace std;
namespace oop244{

   // copy constructor and assignment operator
   AidApp::AidApp(const AidApp&){}
   AidApp& AidApp::operator=(const AidApp&){ return *this; }


   // constructor 
   // copies filename to _filename
   // sets all the _items to null
   // sets _noOfItems to null
   // loads the Records
   AidApp::AidApp(const char* filename){

      strcpy(_filename, filename);

      for (int i = 0; i < MAX_NO_RECS; i++){
         _items[i] = NULL;
      }

      _noOfItems = 0;

      loadRecs();
   }

   // Menu() displays the menu as follows and waits for the user to 
   // select an option. 
   // if the selection is valid, it will return the selection
   // if not it will return -1
   // this funtion makes sure there is no characters left in keyboard
   // and wipes it before exit.
   int AidApp::menu(){

      int selection;

      cout << endl << endl;
      cout << "+----------------------------------------+" << endl;
      cout << "| Disaster Aid Supply Management Program |" << endl;
      cout << "+----------------------------------------+" << endl;
      cout << "                                         |" << endl;
      cout << " 1 - List items                          |" << endl;
      cout << " 2 - Add Non-food item                   |" << endl;
      cout << " 3 - Add Perishable item                 |" << endl;
      cout << " 4 - Update item quantity                |" << endl;
      cout << "                                         |" << endl;
      cout << "    ********************************     |" << endl;
      cout << "             Sort Items:                 |" << endl;
      cout << " 6 - by price                            |" << endl;
      cout << " 7 - by quantity                         |" << endl;
      cout << " 8 - by most needed items                |" << endl;
      cout << " 9 - sort alphabetically                 |" << endl;
      cout << "                                         |" << endl;
      cout << "    ********************************     |" << endl;
      cout << "             Searh Item:                 |" << endl;
      cout << " 11 - by name                            |" << endl;
      cout << " 12 - by upc                             |" << endl;
      cout << "                                         |" << endl;
      cout << " 10 - Delete item                        |" << endl;
      cout << " 0  - exit program                       |" << endl;
      cout << "_________________________________________|" << endl;
      cout << "Enter: ";

      cin >> selection;

      cout << endl;

      return (selection >= 0 && selection <= 12) ? selection : -1;

   }


   // lists all the items in linear format on the screen 

   void AidApp::listItems()const{

      system("cls");
      double totalCost = 0;
      cout << "____________________________________________________________________________" << endl;
      cout << "     |        |                    |       |    |    |          |          |" << endl;
      cout << " Row | UPC    | Item Name          | Cost  | QTY|Need| Unit     | Expiry   |" << endl;
      cout << "_____|________|____________________|_______|____|____|__________|__________|" << endl;

      for (int i = 0; i < _noOfItems; i++){

         cout << right << setw(4) << i + 1 << " | "; // Row 
         cout << *_items[i] << endl;

         totalCost += *_items[i];
      }

      cout << "----------------------------------------------------------------------------" << endl;
      cout << " Total cost of support: $" << fixed << setprecision(2) << totalCost << endl << endl;
      
      system("pause");  
   }


   // opens the file for writing
   // stores the items in the file
   // closes the file
   void AidApp::saveRecs(){

      datafile.open(_filename, ios::out);

      for (int readIndex = 0; readIndex < _noOfItems; readIndex++){

         _items[readIndex]->store(datafile);
      }

      datafile.close();

   }


   // Opens the file for reading, if it does not exist, it will create an
   // empty file and exits otherwise :
   // Loads Records from the file overwriting the old ones pointed by item.
   // This function makes sure when loading records into _item pointers, they 
   // are deallocated before if they are already pointing to an item
   // closes the file

   void AidApp::loadRecs(){


      char id = 0; //stores id of an item
      int readIndex = 0;

      /*  open file for reading only  */
      datafile.open(_filename, ios::in);

      /*  if the file does not exist - create it  */
      if (datafile.fail()){

         datafile.clear();
         datafile.close();

         datafile.open(_filename, ios::out);
         datafile.close();
      }
      else{


         while (!datafile.fail()){


            if (_items[readIndex] != NULL){

               delete  _items[readIndex];
               _items[readIndex] = NULL;
            }


            datafile >> id;

            if (id == 'P'){

               // create Perishable item
               _items[readIndex] = new Perishable;
               if (_items[readIndex] == NULL)
                  cerr << "Could not dynamically allocate memory for Perishable item" << endl;

            }
            else if (id == 'N'){

               // create NFI item
               _items[readIndex] = new NFI;
               if (_items[readIndex] == NULL)
                  cerr << "Could not dynamically allocate memory for Perishable item" << endl;

            }
            else
               cerr << "Invalid item specification(not N or P)" << endl;



            if (id == 'P' || id == 'N'){

               /* ignores comma */
               datafile.ignore();

               /* loads the item from the file */
               _items[readIndex]->load(datafile);


               readIndex++;
            }


         }

         _noOfItems = readIndex - 1;
      }

      datafile.close();
   }

   // Searchers for the item in the _items array with the same UPC.
   // if found, it will display the item in non-linear format and then 
   // asks for the value of the items purchased, and if the value does not exceed
   // the number needed to fulfill the requirement, it will update the quantity onhand
   // value of the found record and then saves all the records to the file, overwriting 
   // the old values
   void AidApp::updateQty(const char* UPC){

      int index = SearchItems(UPC);
      int qty;

      if (index != -1){

         _items[index]->display(cout, false);
         cout << "Please enter the number of purchased items: ";
         cin >> qty;

         if (cin.fail()){
            cerr << "Invalid Quantity value!" << endl;
         }
         else{

            int needed = _items[index]->qtyNeeded();
            int currentQTY = _items[index]->quantity();

            if (qty <= needed - currentQTY){
               *_items[index] += qty;
            }
            else{

               int extra = qty - (needed - currentQTY);
               *_items[index] += (needed - currentQTY);
               cout << "Too much items, only " << needed << " is needed, please return the extra " << extra << " items." << endl;
            }

            saveRecs(); 
            cout << "Updated!" << endl;

         }
      }
      else
         cerr << "Not found!" << endl;



      /*   flush keyboard   */
      cin.ignore(2000, '\n');
   }


   // searches for an item in the _items array for the same upc
   // if found it will return the index of the found item in _items
   // otherwise returns -1
   int AidApp::SearchItems(const char* upc)const{

      for (int i = 0; i < _noOfItems; i++){

         if (strcmp(_items[i]->upc(), upc) == 0)
            return i;
      }

      return -1;
   }

   int AidApp::SearchItemsName(const char* name){

      

      for (int i = 0; i < _noOfItems; i++){
         if (strcmp(_items[i]->name(), name) == 0)
            return i;

      }

      return -1;
   }

   void AidApp::SearchMenu(bool SearchByName){

      char string[30];
      int index;
      double totalCost = 0;


      if (SearchByName){

         cin.ignore(2000, '\n');
         cout << "Enter a name for the item: ";
         cin.getline(string, 30);
         index = SearchItemsName(string);
      }
      else{

         cin.ignore(2000, '\n');
         cout << "Enter a upc for the item: ";
         cin.getline(string, 30);
         index = SearchItems(string);
      }

      if (index != -1){
         cout << "____________________________________________________________________________" << endl;
         cout << "     |        |                    |       |    |    |          |          |" << endl;
         cout << " Row | UPC    | Item Name          | Cost  | QTY|Need| Unit     | Expiry   |" << endl;
         cout << "_____|________|____________________|_______|____|____|__________|__________|" << endl;

         cout << right << setw(4) << index + 1 << " | "; // display the row number
         _items[index]->display(cout);
         cout << endl;

         totalCost += *_items[index];

         cout << "----------------------------------------------------------------------------" << endl;
         cout << " Total cost of support: $" << fixed << setprecision(2) << totalCost << endl << endl;

         system("pause");
         system("cls");
      }
   }



   // creates a new item (NFI or Perishable) based on the argument
   // recieved dynamically, asks the user to fill in the values
   // if the user fills the values with no mistake, it will open the file 
   // for writing, and then stores the item in the file.
   // and print a proper message. 
   // if the user makes a mistake (cin fails) it will only display the item
   // to show the error.
   // in any way it will delete the item before exiting the function
   void AidApp::addItem(bool isPerishable){

      bool hasError = false; // has no error 

      Item *item; // stores new item


      if (isPerishable){

         item = new Perishable;
         cin >> *item;
         if (cin.fail()){
            hasError = true;
            cout << *item;
         }

      }
      else {

         item = new NFI;
         cin >> *item;

         if (cin.fail()){
            hasError = true;
            cout << *item;
         }
      }

      
      


      if (!hasError){

         /* check if the upc of the new item is unique */
         if (SearchItems(item->upc()) != -1){
            hasError = true;
            cerr << "*Upc is not unique, the item will not be added" << endl;
         }
         else {

            _items[_noOfItems] = item;
            _noOfItems++;
            saveRecs();
            loadRecs();
         }
            cout << "Item added" << endl;
      }




   }

   // diplays the menu and receives the user selection
   // if valid, it will preform the action requsted:
   // 1, lists the items in the file on the screen
   // 2 and 3, adds the item and then re-loads the records
   //     from the file into the AidApp
   // 4, gets a UPC and then updates the quantity of it
   // 0, exits the program.
   int AidApp::run(){

      int UserSelect;

      do {
         UserSelect = menu();
         switch (UserSelect){
         case 1:
            listItems();
            break;
         case 2:
            addItem(false);

            /* clean error and buffer */
            cin.clear();
            cin.ignore(2000, '\n');
            break;
         case 3:
            addItem(true);

            /* clean error and buffer */
            cin.clear();
            cin.ignore(2000, '\n');
            break;
         case 4:
            char upc[MAX_UPC_LEN];
            cout << "Please enter the UPC: ";

            /* clean error and buffer */
            cin.clear();
            cin.ignore(2000, '\n');

            cin.getline(upc, MAX_UPC_LEN);
            updateQty(upc);


            break;
         case 6:
            SortByPrice();
            break;
         case 7:
            SortByQuantity();
            break;
         case 8:
            SortByQtyNeeded();
            break;
         case 9:
            SortAlphabetically();
            break;
         case 10:
            deleteItems();
            break;
         case 11:
            SearchMenu(true);
            break;
         case 12:
            SearchMenu(false);
            break;
         case 0:
            break;
         default:

            cerr << " === Invalid Selection, try again. === " << endl;

            /* clean error and buffer */
            cin.clear();
            cin.ignore(2000, '\n');
            break;
         }
      } while (UserSelect != 0);


      cout << "Goodbye!!!" << endl;
      return 0;


   }



   /* Delete Items that has been selected by user via upc */
   // 1. Prompt User for upc
   // 2. Find upc in array of Items and delete it, 
   //    if upc was not found exit from the function
   // 3. Shift array by one due to deleted Items 

   void AidApp::deleteItems(){

      char upc[MAX_UPC_LEN];
      bool hasError = false;
      loadRecs();
      listItems();
      cout << "Enter the upc for the item that you want to delete" << endl;
      cin.ignore(2000, '\n');
      cin.getline(upc, MAX_UPC_LEN);

      int indexToDelete = SearchItems(upc);


      if (indexToDelete != -1)
         _items[indexToDelete] = NULL;
      else{
         hasError = true;
         cerr << "Could not find the upc:" << upc << endl;
      }

      
      if (!hasError){
         int j = 0;
         for (int i = 0; i < _noOfItems; i++){

            if (_items[j] == NULL) //shift the array because 1 item was deleted 
               j++;

            _items[i] = _items[j];

            j++;
         }

         _noOfItems--;

         saveRecs();
         loadRecs();
         if (_items[indexToDelete] != NULL)
            cout << "The item with upc: " << upc << " has been deleted successfully" << endl;
         else
            cerr << "Could not delete the item" << endl;
      }
   }


   /* SORT ITEMS BY PRICE */
   // 1.sort items by price 
   // 2.display sorted Items
   // 3.reset order of Items to default veiw before exit from the function
   void AidApp::SortByPrice(){

      loadRecs();
      bool isNotSort; 
      
      
      do { 
         isNotSort = false;
      
         for (int i = 0; i < _noOfItems - 1; i++){

            if (_items[i]->price() < _items[i + 1]->price()){
               isNotSort = true;
               Item* temp;
               temp = _items[i];
               _items[i] = _items[i + 1];
               _items[i + 1] = temp;
            }
         }

      } while (isNotSort);


      
      displaySortedItems();

      /* reset items order to default view */
      loadRecs();

   }

   void AidApp::SortByQuantity(){

      loadRecs();
      bool isNotSort;


      do {
         isNotSort = false;

         for (int i = 0; i < _noOfItems - 1; i++){

            if (_items[i]->quantity() < _items[i + 1]->quantity()){
               isNotSort = true;
               Item* temp;
               temp = _items[i];
               _items[i] = _items[i + 1];
               _items[i + 1] = temp;
            }
         }

      } while (isNotSort);



      displaySortedItems();

      /* reset items order to default view */
      loadRecs();

   }

   void AidApp::SortByQtyNeeded(){

      loadRecs();
      bool isNotSort;


      do {
         isNotSort = false; // it is sorted 

         for (int i = 0; i < _noOfItems - 1; i++){

            if (_items[i]->qtyNeeded() < _items[i + 1]->qtyNeeded()){
               isNotSort = true; // it is not sorted
               Item* temp;
               temp = _items[i];
               _items[i] = _items[i + 1];
               _items[i + 1] = temp;
            }
         }

      } while (isNotSort);



      displaySortedItems();

      /* reset items order to default view */
      loadRecs();

   }

   void AidApp::SortAlphabetically(){

      char ascii;
      int j;
      loadRecs();
      bool isNotSort;
     


      do {
         isNotSort = false;
          0;
         for (int i = 0; i < _noOfItems-1; i++){
            j = 0;
            /* if first characters are the same move on to the next one*/
            if ((int)_items[i]->name()[j] == (int)_items[i + 1]->name()[j])
               j++;


            if ((int)_items[i]->name()[j] > (int)_items[i + 1]->name()[j]){


               isNotSort = true;
               Item* temp;
               temp = _items[i];
               _items[i] = _items[i + 1];
               _items[i + 1] = temp;
            }
         }

      } while (isNotSort);


      
        

      displaySortedItems();

      /* reset items order to default view */
      loadRecs();

   }

   void AidApp::displaySortedItems(){
      double totalCost = 0;
      cout << "____________________________________________________________________________" << endl;
      cout << "     |        |                    |       |    |    |          |          |" << endl;
      cout << " Row | UPC    | Item Name          | Cost  | QTY|Need| Unit     | Expiry   |" << endl;
      cout << "_____|________|____________________|_______|____|____|__________|__________|" << endl;
      for (int i = 0; i < _noOfItems; i++){
         cout << right << setw(4) << i + 1 << " | "; // display the row number
         _items[i]->display(cout);
         cout << endl;

         totalCost += *_items[i];
      }
      cout << "----------------------------------------------------------------------------" << endl;
      cout << " Total cost of support: $" << fixed << setprecision(2) << totalCost << endl << endl;

      system("pause");
      system("cls");
   }


}