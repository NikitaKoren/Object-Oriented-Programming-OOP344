//includes go here
#include "NFI.h"
#include <fstream>
#include <iostream>
#include <iomanip>


namespace oop244{
  // constructor
   NFI::NFI() : Item("", "", 0, 1){} 

  
   std::fstream& NFI::store(std::fstream& file)const{

      file << "N" << "," << upc() << "," << name() << "," << price() << "," << quantity() << "," << qtyNeeded() << std::endl;
      return file;
   }



   std::fstream& NFI::load(std::fstream& file){


      char _upc[MAX_UPC_LEN];
      char _name[30];
      double _price;
      int _quantity;
      int _qtyNeeded;
      
      


      //Reads from the file 
      file.getline(_upc, MAX_UPC_LEN + 1, ',');
      file.getline(_name, 30, ',');
      file >> _price;
      file.ignore();
      file >> _quantity;
      file.ignore();
      file >> _qtyNeeded;


      //Setting the variables  
      upc(_upc);
      name(_name);
      price(_price);
      quantity(_quantity);
      qtyNeeded(_qtyNeeded);
      

      return file;
   }

    
   std::ostream& NFI::display(std::ostream& ostr, bool linear)const{
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
               std::right << std::setw(4) << qtyNeeded() << 
               std::right << "|" << std::setw(4) <<
               std::right << std::setw(11) << "|" << std::right << std::setw(11) << "|";


         }
         else        // Prints one member variable per line
         {
            
            ostr << "Upc: "   << upc()    << std::endl;
            ostr << "Name: "  << name()   << std::endl;
            ostr << "Price: " << std::fixed << std::setprecision(2) << price() << std::endl;
            ostr << "Price after tax: " << std::fixed << std::setprecision(2)  << cost() << std::endl;
            ostr << "Quantity On Hand: " << quantity()  << std::endl;
            ostr << "Quantity Needed: "   << qtyNeeded() << std::endl;
         }
      }
     
      return ostr;
   }


   std::istream& NFI::conInput(std::istream& is){

      
      char _upc[MAX_UPC_LEN];
      char _name[30];
      double _price;
      int _quantity;
      int _qtyNeeded;
      bool hasError = false; // has no errors 


      _err.clear();
      is.ignore(2000, '\n');
      std::cout << "+----------------------+" << std::endl;
      std::cout << "| Non-Food Item Entry: |" << std::endl;
      std::cout << "+----------------------+" << std::endl;
      std::cout << " Upc: ";
      is.getline(_upc, MAX_UPC_LEN+1);
      upc(_upc);

      std::cout << " Name: ";
      is.getline(_name, 30);
      name(_name);

      //reads and sets price
      std::cout << " Price: ";
      is >> _price;
      if (is.fail()){
         hasError = true;
         _err.message("Invalid Price Entry");
      }
      else
         price(_price);
         

      //reads and sets quantity
      if (!hasError){
         std::cout << " Quantity On hand: ";
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
         std::cout << " Quantity Needed: ";
         is >> _qtyNeeded;
         if (is.fail()){
            hasError = true;
            _err.message("Invalid Quantity Needed Entry");
         }
         else
            qtyNeeded(_qtyNeeded);
      }
      

      return is;
   }


}