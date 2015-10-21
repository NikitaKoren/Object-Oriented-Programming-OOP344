#ifndef __244_DATE_H__
#define __244_DATE_H__
// header file includes
#include "general.h"
#include <iostream>

namespace oop244{
// Error code values gos here
#define NO_ERROR   0  //--No error the date is valid
#define CIN_FAILED 1  //--istream failed when entering information
#define YEAR_ERROR 2  //--Year value is invalid
#define MON_ERROR  3  //--Month value is invalid
#define DAY_ERROR  4  //--Day value is invalid

  class Date{
  private:
    // private member variables 
    int _year;
    int _mon;
    int _day;
    int _readErrorCode;
    // privaet memeber functions and setters
    int value()const;
    void errCode(int errorCode);
    bool validate();
  public:
    // constructor
     Date();
     Date(int year, int month, int day);

    // operator overloads
     bool operator==(const Date& D)const;
     bool operator!=(const Date& D)const;
     bool operator<(const Date& D)const;
     bool operator>(const Date& D)const;
     bool operator<=(const Date& D)const;
     bool operator>=(const Date& D)const;


    // IO member funcions
     std::istream& read(std::istream& istr);
     std::ostream& write(std::ostream& ostr)const;

    // public member fucntions and getters 
    int mdays()const;
    int errCode()const;
    bool bad()const;

  };
  // operator << and >> overloads prototypes for ostream and istream go here
  std::istream& operator>>(std::istream& is, Date& RO);
  std::ostream& operator<<(std::ostream& os, const Date& RO);

}
#endif