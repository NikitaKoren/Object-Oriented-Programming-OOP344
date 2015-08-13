#include "Date.h"
#include "general.h"
#include <iomanip>
#include <iostream>
using namespace std;
namespace oop244{
  // returns a uniqe value out of date
  // this value is used to compare two dates
  int Date::value()const{ 
    return _year * 372 + _mon * 31 + _day;
  }

  // validate(), this is an optional private function to write
  // for validation logic and setting the _readErrorCode.
  // see the read() funciton description for more detail
  bool Date::validate(){

     bool noError = true; // means error was not found 


     if (_year < 2000 || _year > 2030){
        errCode(YEAR_ERROR);
        noError = false; // means error was found
     }

     else if (_mon < 1 || _mon > 12){
        errCode(MON_ERROR);
        noError = false; // means error was found
     }

     else if (_day < 1 || _day > mdays()){
        errCode(DAY_ERROR);
        noError = false; // means error was found
     }
     else
        errCode(NO_ERROR);


     return noError;
  }

  void Date::errCode(int errorCode){
     _readErrorCode = errorCode;
  }



  // mday():
  // returns the day of the month. 
  // _mon value must be set for this to work
  // if _mon is invalid, this function returns -1
  // leap years are considered in this logic

  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
  }


  // constructor 
  Date::Date(){
     _year = 0;
     _mon = 0;
     _day = 0;
     _readErrorCode = NO_ERROR;
  }

  Date::Date(int year, int mon, int day){
     _year = year;
     _mon = mon;
     _day = day;
     _readErrorCode = NO_ERROR;
  }

  // member fucntions 
  int Date::errCode()const{
     return _readErrorCode;
  }

  bool Date::bad()const{
     return (_readErrorCode != 0 ) ? true : false;
  }


  // operators
  bool Date::operator==(const Date& D)const{
     return (this->value() == D.value() ? true : false);
  }
  bool Date::operator!=(const Date& D)const{
     return (this->value() != D.value() ? true : false);
  }
  bool Date::operator<(const Date& D)const{
     return (this->value() < D.value() ? true : false);
  }
  bool Date::operator>(const Date& D)const{
     return (this->value() > D.value() ? true : false);
  }
  bool Date::operator<=(const Date& D)const{
     return (this->value() <= D.value() ? true : false);
  }
  bool Date::operator>=(const Date& D)const{
     return (this->value() >= D.value() ? true : false);
  }




  // IO funtions
  std::istream& Date::read(std::istream& istr){
     
     //read year, mon, day
     istr >> _year;
     istr.ignore(); // ignores "/"

     istr >> _mon;
     istr.ignore();

     istr >> _day;

     if (istr.fail())
        errCode(CIN_FAILED);
     else
        validate();//valiates values(year, mon, day) to be in range (see general.h)
        

     return istr;
  }

  std::ostream& Date::write(std::ostream& ostr)const {
     
     if (_day < 10 && _mon < 10)
        ostr << _year << "/0" << _mon << "/0" << _day;
     else if (_day < 10)
        ostr << _year << "/" << _mon << "/0" << _day;
     else if (_mon < 10)
        ostr << _year << "/0" << _mon << "/" << _day;
     else 
        ostr << _year << "/" << _mon << "/" << _day;

     return ostr;
  }   
  

  // non-memeber operator overloads
  std::istream& operator>>(std::istream& is, Date& RO){
     return RO.read(is);
  }

  std::ostream& operator<<(std::ostream& os, const Date& RO){
     return RO.write(os);
  }


}
