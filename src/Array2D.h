#include <cstring>
#include <iostream>
#pragma once

template <typename T>

class Array2D{
private:
    T* array;
    int width, height;
public:

    Array2D(const int x,const int y){
        width = x;
        height = y;
        array = new T[x * y];
    }

    Array2D(Array2D const &other){
        this->height = other.height;
        this->width = other.width;
        
        array = new T[other.width*other.height];
        
        for(int i{}; i < other.height*other.width; ++i){
            this->array[i] = other.array[i];
        }
    }

    Array2D& operator=(Array2D const &other){
        if( this == &other){
            return *this;
        }

        delete[] array;

        this->height = other.height;
        this->width = other.width;
        
        array = new T[other.width*other.height];
        
        for(int i{}; i < other.height*other.width; ++i){
            this->array[i] = other.array[i];
        }

        return *this;
    }

    void fill(T fill){
        for(int i{}; i < width*height; ++i) array[i] = fill;
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

    T& operator[](const int i){
        return array[i];
    }

};

