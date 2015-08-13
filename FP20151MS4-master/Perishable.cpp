// includes go here
#include "Perishable.h"
#include <fstream>
#include <iostream>
#include <iomanip>

namespace oop244{
   // constructor
   Perishable::Perishable() : Item("", "", 0, 1, false){
      strcpy(_unit, "");
   }

   Perishable::~Perishable(){}

   // Setters and getters 
   const Date& Perishable::expiry()const{
      return _expiry;
   }
   void Perishable::expiry(const Date &value){
      _expiry = value;
   }
   const char* Perishable::unit()const{
      return _unit;
   }
   void Perishable::unit(const char* value){
      strncpy(_unit, value, 11);
   }

  // fstream& Perishable::store(fstream& file)const
   std::fstream& Perishable::store(std::fstream& file)const{

      file << "P" << "," << upc() << "," << name() << "," << price() << "," << _unit << "," << quantity() << "," << qtyNeeded() << "," << _expiry << std::endl;
      return file;
   }




  //fstream& Perishable::load(fstream& file)
   std::fstream& Perishable::load(std::fstream& file){

      char _upc[MAX_UPC_LEN + 1];
      char _name[30];
      double _price;
      int _quantity;
      int _qtyNeeded;
      Date _expiry;



      //Reads from the file 
      file.getline(_upc, MAX_UPC_LEN, ',');
      file.getline(_name, 30, ',');
      file >> _price;
      file.ignore();
      file.getline(_unit, 11, ',');
      file >> _quantity;
      file.ignore();
      file >> _qtyNeeded;
      file.ignore();
      file >> _expiry;

      //Setting the variables  
      upc(_upc);
      name(_name);
      price(_price);
      quantity(_quantity);
      qtyNeeded(_qtyNeeded);
      expiry(_expiry);

      return file;
   }



  
  //ostream& Perishable::display(ostream& os, bool linear)const
   std::ostream& Perishable::display(std::ostream& ostr, bool linear)const{

      if (!_err.isClear())
      {
         ostr << _err;
      }
      else
      {

         if (linear) // Prints the Item values separated by Bar “|” in one line
         {
            ostr << std::left << std::setw(MAX_UPC_LEN) << upc() << "|" <<
               std::left << std::setw(20) << name() << "|" <<
               std::right << std::setw(7) << std::fixed << std::setprecision(2) << cost() << "|" <<
               std::right << std::setw(4) << quantity() << "|" <<
               std::right << std::setw(4) << qtyNeeded() << "|" <<
               std::left << std::setw(10) << unit() << "|" << expiry() << "|";


         }
         else        // Prints one member variable per line
         {
            
            ostr << "upc: " << upc() << std::endl;
            ostr << "name: " << name() << std::endl;
            ostr << "price: " << std::fixed << std::setprecision(2) << price() << std::endl;
            ostr << "Price after tax: " << std::fixed << std::setprecision(2) << cost() << std::endl;
            ostr << "Quantity On hand: " << quantity() << std::endl;
            ostr << "Quantity Needed: " << qtyNeeded() << std::endl;
            ostr << "Unit: " << unit() << std::endl;
            ostr << "Expiry date: " << expiry() << std::endl;
         }
      }

      return ostr;

   }
  
  
  
  // istream& Perishable::conInput(istream& is)
   std::istream& Perishable::conInput(std::istream& is){
      char _upc[MAX_UPC_LEN];
      char _name[50];
      double _price;
      int _quantity;
      int _qtyNeeded;
      bool hasError = false; // has no errors 


      _err.clear();
      std::cin.ignore(2000, '\n');

      std::cout << "Perishable Item Entry:" << std::endl;

      std::cout << "upc: ";
      is.getline(_upc, MAX_UPC_LEN + 1);
      upc(_upc);

      std::cout << "name: ";
      is.getline(_name, 50);
      name(_name);

      //reads and sets price
      std::cout << "price: ";
      is >> _price;
      if (is.fail()){
         hasError = true;
         _err.message("Invalid Price Entry");
      }
      else
         price(_price);


      //reads and sets quantity
      if (!hasError){
         std::cout << "Quantity On hand: ";
         is >> _quantity;
         if (is.fail()){
            hasError = true;
            _err.message("Invalid Quantity Entry");
         }
         else
            quantity(_quantity);
      }


      //reads and sets qtyNeeded
      if (!hasError){
         std::cout << "Quantity Needed: ";
         is >> _qtyNeeded;
         if (is.fail()){
            _err.message("Invalid Quantity Needed Entry");
            hasError = true;
         }
         else
            qtyNeeded(_qtyNeeded);
      }

      //reads and sets Unit
      if (!hasError){
         std::cout << "Unit: ";
         is.ignore();
         is.getline(_unit, 11);
         unit(_unit);
      }


      //reads and sets date
      if (!hasError){
         std::cout << "Expiry date (YYYY/MM/DD) : ";
         is >> _expiry;
 
         switch (_expiry.errCode()){
         case 1:
            _err.message("Invalid Date Entry");
            is.setstate(std::ios::failbit);
            break;
         case 2:
            _err.message("Invalid Year in Date Entry");
            is.setstate(std::ios::failbit);
            break;
         case 3:
            _err.message("Invalid Month in Date Entry");
            is.setstate(std::ios::failbit);
            break;
         case 4:
            _err.message("Invalid Day in Date Entry");
            is.setstate(std::ios::failbit);
            break;
         default:
            break;
         }
              
         if (is.fail())
            hasError = true;

            

      }
      return is;

   }
}
