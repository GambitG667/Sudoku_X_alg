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
    std::cout << "Деструктор отработал\n";
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

void Array2D::pprintArray(int number_digits){

    /*Реализовать красивый вывод таблицы*/

    for (int y{}; y < height; ++y) {
        for (int x{}; x < width; ++x) {
            int element{array[y * width + x]};
            int num_dig_in_element{};
            if (x < width - 1) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

int &Array2D::operator()(const int x, const int y) {
    return array[y * width + x];
}