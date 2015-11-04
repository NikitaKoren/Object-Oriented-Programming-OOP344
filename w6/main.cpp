// Workshop 6 - Lambda Expression
// w6.cpp

#include <iostream>
#include "Grades.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << argv[0] <<
        ": incorrect number of arguments\n";
        std::cerr << "Usage: " << argv[0] << " file_name\n";
        return 1;
    }


    Grades grades(argv[1]);

    // define the lambda expression for letter
    auto letter = [](float grade) -> string {

        return
                grade >= 90? string("A+") :
                grade >= 80? string("A")  :
                grade >= 75? string("B+") :
                grade >= 70? string("B")  :
                grade >= 65? string("C+") :
                grade >= 60? string("C")  :
                grade >= 55? string("D+") :
                grade >= 50? string("D")  :
                string("F");
    };



    grades.displayGrades(std::cout, letter);
    std::cout << "Press any key to continue ... ";
    std::cin.get();
}