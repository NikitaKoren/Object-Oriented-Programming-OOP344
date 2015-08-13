#include "Streamable.h"


namespace oop244{
  // destructor:
   Streamable::~Streamable(){}


  // Non-memenber operator overoad implementation for cin and cout:
   std::istream& operator>>(std::istream& is, Streamable& RO){
      return RO.conInput(is);
   }

   std::ostream& operator<<(std::ostream& os, Streamable& RO){
      return RO.display(os);
   }


}