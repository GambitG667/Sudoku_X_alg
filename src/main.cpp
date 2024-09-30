#include <iostream>
#include "Array2D.h"


int main(){


    Array2D matrix(9,9);
    for(int y{}; y < 9; ++y) for(int x{}; x < 9; ++x)
    {
        matrix(x, y) = (x+y)%10;
    }
    matrix.pprintArray();

    std::cout<< "\nhello worl blat\n";


    return 0;
}