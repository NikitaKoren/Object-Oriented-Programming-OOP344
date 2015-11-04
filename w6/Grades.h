#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "string"
#include <iomanip>

using namespace std;

// Class Grades holds the grades for all students in a course.
class Grades {

    //associative arrays
    float*  _grade;        // stores student's grade
    string* _studentID;    // stores student's ID
    int _arr_size;         // stores amount of elements in the arrays


    //prevent the copying, moving and assigning of an object
    Grades (const Grades&)           = delete; // copy
    Grades& operator=(const Grades&) = delete; // assignment
    Grades(Grades&&)                 = delete; // move
    Grades&operator=(Grades&&)       = delete; // move assignment


public:

    Grades(char* filename) {

        int size = 5; //default size of a file
        ifstream file(filename);
        if(!file) {
           throw "Failed to open a file!";
        }


        string* line;
        line = new string [size];
        int count = 0; //count the amount of records in a file

        cout << " Read from the file" << endl;
        //read from the file into line
        while(getline(file, line[count])){

            // allocates more memory (if needed)
            if(count == size - 1) {
                cout << "allocate more memory, size: " << size << " * 2 = " << size*2 << endl;


                //temp variable to store data from line
                string temp[size];

                //copy data into temp array
                for(int i = 0; i < size; i++)
                    temp[i] = line[i];

                delete [] line;

                //allocate more memory
                line = new string[size*2];

                //copy old data into new allocated array
                for(int i = 0; i < size; i++)
                    line[i] = temp[i];

                // increase size
                size *= 2;
            }

            count++;
        }

        file.close();

        cout << "amount of elements in the file: " << count << endl;
        _arr_size = count; // set the final amount of elements

        //allocate memory
        _grade     = new float[_arr_size];
        _studentID = new string [_arr_size];


        // save data from a file into associative arrays in a class
        size_t length;
        size_t space;
        for(int i = 0; i < _arr_size; i++) {

            //split string into 2 variables
            length = line[i].length();
            space = line[i].find(' ');

            _studentID[i] = line[i].substr(0,space);     //save into the first array
            _grade[i]     = stof(line[i].substr(space)); //convert to float and save into the second array

        }

        delete [] line;
    }

    //letter is a lambda function in main
   void displayGrades(ostream& os, string (*letter)(float)) const {

       os << "Grade description: " << endl;

       for(int i = 0; i < _arr_size; i++)
        os << _studentID[i] << " " << fixed << setprecision (2) << _grade[i] << " " << letter(_grade[i]) << endl;
   }

    ~Grades(){

        delete [] _grade;
        delete [] _studentID;
    }



};
