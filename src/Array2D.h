#include <iostream>
#pragma once

template <typename T>

class Array2D{
private:
    T* array;
    int width, height;
public:

    Array2D(const int x,const int y, T fill){
        width = x;
        height = y;
        array = new T[x * y]{0};
        std::fill_n(array, (x * y), fill);
    }
    
    ~Array2D(){
        delete[] array;
    }

    void printArray(){
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
    
    T& operator()(const int x, const int y){
        return array[y * width + x];
    }

};

