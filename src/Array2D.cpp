#include "Array2D.h"
#include <iostream>

Array2D::Array2D(const int x, const int y) {
    width = x;
    height = y;
    array = new int[x * y]{0};
    std::fill_n(array, (x * y), 0);
}

Array2D::~Array2D() {
    delete[] array;
}

void Array2D::printArray() {
    for (int y{}; y < height; ++y) {
        for (int x{}; x < width; ++x) {
            std::cout << array[y * width + x];
            if (x < width - 1) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

void Array2D::writeLine(int lenth, char simbol, char separator1, char separator2){
    for(int i{}; i<lenth; ++i){
        
        if(i % 12 == 11 && i != 0) std::cout << separator2;
        else if (i%4 == 3 && i != 0) std::cout << separator1;
        else std::cout << simbol;

    }
    std::cout<<"\n";
}

void Array2D::pprintArray(){

    /*Реализовать красивый вывод таблицы*/

    for (int y{}; y < height; ++y) {
        

        for (int x{}; x < width; ++x) {

            if(x == 0) std::cout << " ";

            std::cout << array[y * width + x];

            if (x < width - 1) {
                if (x % 3 == 2) std::cout << " # ";
                else std::cout << " | ";
            }
        }
        std::cout << "\n";
        
        if(y < height-1){

        if (y % 3 == 2) writeLine(4*width-1, '#', '#', '#');
        else writeLine(4*width-1, '-', '|', '#');
        
        }
        
    }
}

int &Array2D::operator()(const int x, const int y) {
    return array[y * width + x];
}