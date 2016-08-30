// Workshop 7 - STL Containers
// iProduct.h

#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace w7 {
    enum TaxType_e {NO_TAX, HST, PST};

    class iProduct {
    public:
        virtual double getCharge() const = 0;
        virtual void display(std::ostream&) const = 0;
    };

    class Product : public iProduct {
        int code;
        double price;
    public:
        Product(int c, double p) : code(c), price(p) {}
        double getCharge() const {

        }

        void display (std::ostream&) const{

        }
    };

    class ProductTaxible : public Product {
        int code;
        double price;
        TaxType_e tt;
    public:
        ProductTaxible(int c, double p, TaxType_e t) : Product(c,p), tt(t) {}
        double getCharge() const {

            double  p;
            switch ( tt ) {
                case HST: return 1.13 * Product::getCharge();
                case PST: return 1.08 * Product::getCharge();
            }
        }

        void display (std::ostream& os) const{

            os << getCharge() << "\n";
            switch ( tt ) {
                case HST: std::cout << "HST\n";
                    break;
                case PST: std::cout << "PST\n";
                    break;
            }
        }
    };

    std::ostream& operator<<(std::ostream& os, const iProduct& ref) {

        ref.display(os);
        return os;
    }
    iProduct* readProduct(std::ifstream& is) {

        TaxType_e tc; //enum
        TaxType_e tt; // I do not know which to use

        iProduct* returnValue = nullptr;
        std::string s;

        //skip this if statment if reached end of file
        if ( getline( is, s) ) {

            std::cout << "read-->" << s << s << "<--\n";

            //looking for a fucking strange character from Bill
            auto cr = s.find("\r");
            if(cr != std::string::npos) {
                std::cout << "found a CR at offset " << cr << "\n";
                s.erase( s.begin() + cr);
            }
            std::cout << "read: -->" << s << "<--\n";

            //process code
            //read one character at a time because it is more reliable
            int index = 0;
            int code = 0;
            while( index < s.size() && isdigit(s[index]) ) {
                //if substract value of '0'(30) you will get a number
                //if it is a digit * by 10 to keep track of thousands and substract 30 from a digit
                code = 10 * code +(s[index] - '0'); // this line calculates a number

                index++;
            }

            std::cout << "code=" << code << "\n";

            //skip white spaces
            while( index < s.size() && isdigit(s[index]) ) {
                index++;
            }

            //process price without decimal points
            double price = 0;
            while( index < s.size() && isdigit(s[index]) ) {
                price = 10 * price + (s[index] - '0');
                index++;
            }

            std::cout << "price=" << price << "\n";

            //process price with decimal points
            if (index > s.size() && s[index] == '.') {
                index++; //skip .
            }


            double scale = 0.1;
            while( index < s.size() && isdigit(s[index]) ) {
                price = 10 * price + (s[index] - '0'); //figure out what number is here
                index++;
                scale *= 0.1; // figure out number of hundreds (.1, .01, .001 etc.)
            }
            std::cout << "price=" << price << "\n"; // price with decimal points

            //skip white spaces
            while( index < s.size() && isdigit(s[index]) ) {
                index++;
            }



            //look for P or H
            if(index < s.size()) {
                switch ( s[index]) {
                    case 'H': tc = HST; //using enum
                        break;
                    case 'P': tc = PST;
                        break;
                    default:
                        throw std::string("Unknown tax code '") + s[index] + "'"; // speech about errors handling(user is not stupid, our code is stupid)
                }
            }

            //choose appropriate class for a product( HST, PST or NO_TAX)
            switch ( tt ) {
                case HST: returnValue = new ProductTaxible(code,price,tt); //using enum
                    break;
                case PST: returnValue = new ProductTaxible(code,price,tt);;
                    break;
                case NO_TAX: returnValue = new Product(code, price);
                default:
                    throw std::string("Unknown tax code '") + s[index] + "'"; // speech about errors handling(user is not stupid, our code is stupid)
            }

        }

        return returnValue; // return nullptr
    }

}