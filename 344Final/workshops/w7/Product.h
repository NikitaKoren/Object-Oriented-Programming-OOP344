#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "iProduct.h"


class Product : public virtual iProduct {
	int code;
	double price;
public:
	Product() {
		code = -1;
		price = -1.00;
	}

	Product(int num, double p) : code(num), price(p) {}

	double getCharge() const{
		return price;
	}

	void display(std::ostream& os) const {
		os << std::setw(10) << std::right << code << "     " <<
			std::setw(6) << std::left << price;
	}
};


class Taxable : public Product {

	double t1;
	double t2;
	char type;
public:
	Taxable(int num, double price, const char t) : Product(num, price) {
		type = t;
	}

	double getCharge() const{
		if (type == 'H'){
			double _t1 = Product::getCharge();
                            double t1=1.13;
			return _t1*t1;
                            
		}
		else if (type == 'P'){
			double _t2 = Product::getCharge();
                            double t2=1.08;
			return _t2*t2;
                           
		} else {
			double _t3 = Product::getCharge();
			return _t3;
		}
	}

	void display(std::ostream& os) const {
		Product::display(os);

                      if(type == 'H')
                          os<<"HST";
                      else if(type == 'P')
                          os<<"PST";
                      else
                           os<<' ';
	}
};

	
	std::ostream& operator<<(std::ostream& os, const iProduct& p) {
		p.display(os);
		return os;
	}

	//read the file
	iProduct* readProduct(std::ifstream& is) {
		iProduct* product = nullptr;

		int num = 0;
		double price = 0.0;
		char tax;
		std::stringstream bufferStream;
		std::string buffer;

		std::getline(is, buffer);
		if (!buffer.empty()) {
			bufferStream << buffer;

			bufferStream >> num >> price;
			if (!bufferStream.eof()){
				bufferStream >> tax;
				product = new Taxable(num, price, tax);
			}
			else product = new Product(num, price);
		}
		return product;
	}

