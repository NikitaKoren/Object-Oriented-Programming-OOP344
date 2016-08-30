#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>

namespace w8
{
    template<class T> class DataTable {
        std::vector<T> x;
        std::vector<T> y;

    public:
        DataTable(std::ifstream &fs, const int FW, const int ND) {

            //read from the file
            float temp_x, temp_y;
            while (fs >> temp_x >> temp_y) {
                x.push_back(temp_x);
                y.push_back(temp_y);
            }

            auto itX = x.begin();
            std::cout << "Display value using '*' : " << *itX << std::endl;
        }

        T mean() const {

            return std::accumulate(y.begin(), y.end(), 0.) / y.size();
        }

        T sigma() const {

            T average, sum, result;
            std::vector<T> new_y;


            //Step 1: find average value
            average = mean();

            //Step 2: Subtract average value from each element in y vector and increase to the power of 2
            int size = y.size();
            int i = 0;
            while(i < size) {
                new_y.push_back(pow((y[i] - average), 2));
                i++;
            }

            //Step 3: Take the sum of values from step 2 and divide by number of elements - 1
            sum = std::accumulate(new_y.begin(), new_y.end(), 0.);
            T nElements = new_y.size() - 1;
            sum = sum / nElements;

            //Step 4: Take root of the number from step 3
            result = sqrt(sum);

            return result;
        }


        T median() const {

            T result;
            std::vector<T> buff;
            buff = y;

            int size = buff.size();
            //Sort in ascending order
            std::sort (buff.begin(), buff.end());

            //find out even or odd
            if(size  % 2 == 0) {

                //Step 1: Take 2 elements in the middle and accumulate elements then divide by 2
                result = (buff[size / 2] + buff[(size / 2) - 1]) / 2;
            }
            else {

                //Step 1: Subtract 1 from size, divide 'size - 1' by 2, take 'element + 1' as a result
                result = buff[(size - 1) / 2 + 1];

            }

            return result;

        }

        // returns the slope and intercept for the data set
        void regression(T& slope, T& y_intercept) const
        {

            if(x.size() == 0) // Do not divide by zero.
                throw std::string("Need 1 or more data points to fit a linear regression line.");

            if(x.size() != y.size())
                throw std::string("What? X+Y sizes are different!");

            // symbols:
            //SX  = sum of X elements: X[i]
            //SY  = sum of Y elements: Y[i]
            //SXX = sum of X squared:  X[i] * X[i]
            //SXY = sum of X * Y crossproducts: X[i] * Y[i]

            double SX = 0.,  SY = 0.,  SXX = 0., SYY = 0.,  SXY = 0.;

            // brute force calculation
            /*
            for (int i = 0; i < setX.size(); i++)
            {
               SX  += setX[i];
               SY  += setY[i];
               SXX += setX[i] * setX[i];
               SYY += setY[i] * setY[i];
               SXY += setX[i] * setY[i];
            }
            */

            // calculate using std::algorithms functions.
            // These may be optimized compared to brute force calculation
            // not a big deal for small counts.  May make a difference for huge counts.
            int n = y.size();
            SX = std::accumulate(x.begin(), x.end(), double(0.)); // easy to understand

            // or alternatively, using accumulate with a function that happens to be a lambda
            SX =   std::accumulate(x.begin(), x.end(), double(0),  // HARDER TO UNDERSTAND!
                              [] (double sum, double element) { return sum + element; }
            );

            SY  =  std::accumulate(y.begin(), y.end(), double(0.)); // easy to understand

            SXX =  std::inner_product(x.begin(), x.end(), x.begin(), double(0.)); // easy to understand

            // or alternatively, using accumulate with a function that happens to be a lambda
            SXX =  std::accumulate(x.begin(), x.end(), double(0.),   // HARDER TO UNDERSTAND!
                              [] (double sum, double element)
                              { return sum + element * element; } // calculate sum of X squared using function
            );
            SYY =  std::inner_product(y.begin(), y.end(), y.begin(), double(0.)); // easy to understand
            SXY =  std::inner_product(x.begin(), x.end(), y.begin(), double(0.));

            // statistics 101: straight line equation
            slope        =  (n*SXY - SX*SY)    / (n*SXX - SX*SX);
            y_intercept  =  (SY    - slope*SX) / n;
        }


        void display(std::ostream &os) const {


            auto itY  = y.begin();

            os << std::left << std::setw(4) << "X";
            os << " - ";
            os << std::left << std::setw(4) << "Y";
            os << std::endl;
            for (auto itX = x.begin(); itX != x.end(); ++itX)
            {
                os << std::setw(4) << std::fixed << std::setprecision(2) << *itX;
                os << " - ";
                os << std::setw(4) << std::fixed << std::setprecision(2) << *itY;
                os << std::endl;
                itY++;
            }
        }


    };

    template <typename ST>
    std::ostream &operator<<(std::ostream& os, const DataTable<ST>& Data){
        Data.display(os);
        return os;
    }

}