#include "Sudoku.h"
#include "Array2D.h"
#include <iostream>


Sudoku::Sudoku(): field(9,9, 7), screan(35, 17, ' ') {
    height_screan = 17;
    width_screan = 35;
}
Sudoku::~Sudoku(){};
void Sudoku::render(){
    char sep_v = '|';
    char sep_g = '-';
    char m_sep = '#';

    for(int i{1}; i < 17; i += 2) write_line(i, false, sep_g);
    for(int i{3}; i < 35; i += 4) write_line(i, true, sep_v);
    for(int i{11}; i < 35; i += 12) write_line(i, true, m_sep);
    for(int i{5}; i < 17; i += 6) write_line(i, false, m_sep);
    for(int j{}, y{}; y < 9; j += 2, ++y) 
        for( int i{1}, x{}; x < 9; i += 4, ++x) 
            screan(i,j) = static_cast<char>('0'+field(x, y));
}

void Sudoku::print(){
    for(int j{}; j < height_screan; ++j){

        for(int i{}; i<width_screan; ++i) std::cout<< screan(i, j);
        
        std::cout << '\n';
    }
    

}

void Sudoku::write_line(int number, bool is_vertical, char fill){
    if(is_vertical){
        for(int i{}; i < height_screan; ++i){
            screan(number, i) = fill;
        }
    }else{
        for(int i{}; i < width_screan; ++i){
            screan(i, number) = fill;
        }
    }
}