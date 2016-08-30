#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <exception>

//include files
#include "iProduct.h"
#include "Product.h"


using namespace std;

namespace w7{

	class Sale {
		fstream fs;
		iProduct* temp;
		std::vector<iProduct*> product;

	public:
		Sale(char* filename){

			std::ifstream fs(filename);
			
			// read from the file
			while (!fs.eof()) {
				temp = readProduct(fs);

				if (temp != nullptr){
					product.push_back(std::move(temp));
				}
			}
			
			fs.close();
		}
		void display(std::ostream& os) const {
			double total = 0.0; // stores total 
			std::cout << endl << "Product No     Cost Taxable" << endl;
			std::cout << std::fixed << std::setprecision(2);
			
			for (auto i = 0; i < product.size(); i++) {
				total += product[i]->getCharge();
				std::cout << *product[i]  << std::endl;
			}

			// display total
			std::cout << "     Total";
			std::cout << std::setw(10) << std::right << total << std::endl;
		}
	};
}
