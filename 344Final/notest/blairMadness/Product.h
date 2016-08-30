// Workshop 7 - STL Containers
// iProduct.h

#pragma once
#include <iostream>
#include <fstream>

namespace w7 {


    class iProduct {
    public:

        virtual double getCharge() const = 0;
        virtual void display(std::ostream &) const = 0;
    };


    /*************/
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

    /*************/
    class ProductTaxible : public Product {
        int code;
        double price;
        TaxType_e tt;
    public:
        ProductTaxible(int c, double p, TaxType_e t) : Product(c,p), tt(t) {}
        double getCharge() const {

            double  p;
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



}
