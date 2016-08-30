#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Product.h"

namespace w7 {
    class Sale {
        std::vector<iProduct*> vecOfProduct;
    public:

        Sale(const char* filename){

            std::ifstream file(filename);
            if(!file) {
                throw std::string("Cannot open a file ") + filename + "'\n'";
            }

            iProduct* p;
            while( p = readProduct( file )) {
                vecOfProduct.push_back(p);
            }

            file.close();
        }


        void display(std::ostream& os) const {

            os << "Product No     Cost Taxable \n";
            double total = 0;

            // ends here
            for(auto e: vecOfProduct) {

                total += e->getCharge();
                e->display(std::cout);
                std::cout << *e << "\n";
            }
            std::cout << "Total    " << total;
        }
    };

} //namespace w7