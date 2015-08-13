// header file includes
#include "Item.h"
#include <new>
#include <cstring>
using namespace std;

namespace oop244{
   //Allocation and Deallocation of Memory
   void Item::allocate(int size){
      deallocate();
      _name = new (nothrow) char[size];
   }

   void Item::deallocate(){
      if (_name){
         delete [] _name;
         _name = char(0);
      }
   }

  // constructors 
   Item::Item(const char* upc, const char* name, double price, int qtyNeeded, bool taxed){
      
      this->upc(upc);
      this->name(name);
      this->price(price);
      this->quantity(0);
      this->taxed(taxed);
      this->qtyNeeded(qtyNeeded);
     
   }

   Item::Item(const Item& item){
      *this = item;
   }
   
  // operator=
   Item& Item::operator=(const Item& RO){
      upc(RO._upc);
      name(RO._name);
      price(RO._price);
      quantity(RO._quantity);
      taxed(RO._taxed);
      qtyNeeded(RO._qtyNeeded);

      return *this;
   }



  // setters 
   void Item::upc(const char* upc){
      strcpy(_upc, upc);
   }

   void Item::name(const char* name){
      _name = char(0);
      allocate(strlen(name) + 1);
      strcpy(_name, name);
   }

   void Item::price(double price){
      _price = price;
   }

   void Item::taxed(bool taxed){
      _taxed = taxed;
   }

   void Item::quantity(int quantity){
      _quantity = quantity;
   }

   void Item::qtyNeeded(int qtyNeeded){
      _qtyNeeded = qtyNeeded;
   }




  // getters
   const char* Item::upc() const{
      return _upc;
   }

   const char* Item::name() const{
      return _name;
   }

   double Item::price() const{
      return _price;
   }

   bool Item::taxed() const{
      return _taxed;
   }

   int Item::quantity() const{
      return _quantity;
   }

   int Item::qtyNeeded() const{
      return _qtyNeeded;
   }

   double Item::cost() const{
      double cost;

      if (_taxed)
         cost = _price + _price * TAX;
      else
         cost = _price;

      return cost;
   }


  // member operator overloads 
   bool Item::operator==(const char* str) const{
      bool result = false;

      if (strcmp(_upc, str) == 0)
         result = true; // the strings the same
      else 
         result = false;
     

      return result;
   }

   int Item::operator+=(const int value){
      _quantity += value;
      return _quantity;
   }


  // non-member operator overload
   double operator+=(double& d, const Item& I){
      d += I.cost() * I.quantity();
      return d;
   }


  // destructor
   Item::~Item(){
      deallocate();
   }
}