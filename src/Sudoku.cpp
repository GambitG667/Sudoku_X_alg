#include "Sudoku.h"
#include "Array2D.h"
#include <iostream>





Sudoku::Sudoku(): field(9,9), screan(35, 17) {
    field.fill(7);
    screan.fill(' ');
    
    height_screan = 17;
    width_screan = 35;
}
Sudoku::~Sudoku(){};
void Sudoku::render(){
    char sep_v = '|';
    char sep_g = '-';
    char m_sep = '#';

    for(int i{1}; i < 17; i += 2) write_line(i, RAW, sep_g);
    for(int i{3}; i < 35; i += 4) write_line(i, COLUM, sep_v);
    for(int i{11}; i < 35; i += 12) write_line(i, COLUM, m_sep);
    for(int i{5}; i < 17; i += 6) write_line(i, RAW, m_sep);
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

void Sudoku::print_field(){
    field.printArray();
}

void Sudoku::write_line(int number, Mode mode, char fill){
    if(mode == COLUM){
        for(int i{}; i < height_screan; ++i){
            screan(number, i) = fill;
        }
    }else{
        for(int i{}; i < width_screan; ++i){
            screan(i, number) = fill;
        }
    }
}

void Sudoku::swap(int number1, int number2, Mode mode){
    int bufer{};
    if(mode==COLUM){
        for(int i{}; i < 9; ++i){
            bufer = field(number1, i);
            field(number1, i) = field(number2, i);
            field(number2, i) = bufer;
        }
    }else{
        for(int i{}; i < 9; ++i){
            bufer = field(i, number1);
            field(i, number1) = field(i, number2);
            field(i, number2) = bufer;
        }
    }
}

void Sudoku::swap_districts(int number1, int number2, Mode mode){
        for(int i{}; i < 3; ++i){
            swap(i+number1*3, i+number2*3, mode);
        }
}

void Sudoku::base_generate(){
    int nat_num[9]={1,2,3,4,5,6,7,8,9};

    for(int district{0}; district < 3; ++district){
        for(int j{}; j < 3; ++j){
            for(int i{}; i < 9; ++i){
                field(i, j+3*district) = nat_num[(i+3*j+district)%9];
            }
        }
    }
}

void Sudoku::random_generate(int seed){
    if(seed % 10 > 5){

        int number_district = seed%7%3;
        
        int number1{seed%3};
        int number2{seed%5%3};
        number2 = number2 == number1 ?  (number2+1) % 3 : number2;
        number1 += number_district*3;
        number2 += number_district*3;
        swap(number1, number2, Mode(seed%2));

    }else{
        int number1 = seed % 3;
        int number2 = seed % 5 % 3;
        number2 = number2 == number1 ?  (number2+1) % 3 : number2;

        swap_districts(number1, number2, Mode(seed%2));
    }
}

void Sudoku::random_generate(){
    if(rand() % 2 == 1){

        int number_district = rand()%3;
        
        int number1{rand()%3};
        int number2{rand()%3};
        number2 = number2 == number1 ?  (number2+1) % 3 : number2;
        number1 += number_district*3;
        number2 += number_district*3;
        swap(number1, number2, Mode(rand()%2));

    }else{
        int number1 = rand() % 3;
        int number2 = rand() % 3;
        number2 = number2 == number1 ?  (number2+1) % 3 : number2;

        swap_districts(number1, number2, Mode(rand()%2));
    }
}    


int Cell::number_of_variants(){
    int result{};
    for(int i: character_vector) result += i;
    return result;
}


Array2D<int> Solver::solve(Array2D<int> field){
    Array2D<int> result = field;


    Array2D<Cell> matrix(9,9);
    
    for(int i{0}; i < 9*9; ++i){
        if(result[i] != 0){
            matrix[i].is_solved = true;
            matrix[i].value = result[i];
        }
    }
    
    check_variants(matrix);

    while(is_solved(matrix) == NOTSOLVED){
        for(int i{}; i < 9*9; ++i){
            if(matrix[i].is_solved) continue;
            if(matrix[i].number_of_variants() == 1){for(int j{1}; j<10; ++j){
                if(matrix[i].character_vector[j] != 0){
                    matrix[i].value = j;
                    matrix[i].is_solved = true;
                }                
            }
            }
        }
        check_variants(matrix);
    }


    for(int i{}; i < 9*9; ++i) result[i] = matrix[i].value;

    return result;
}

void Solver::check_variants(Array2D<Cell> &matrix){
    for(int i{}; i < 9*9; ++i){

        for(int j{}; j < 9*9; ++j){
            
            if(matrix[j].is_solved) continue;

            if((i/9 == j/9 || i%9 == j%9 || (i/9/3==j/9/3 && i%9/3==j%9/3)) && i != j){
                matrix[j].character_vector[matrix[i].value] = 0;
            }
        }
    }



}

Status Solver::is_solved(Array2D<Cell> &matrix){
    bool result{true};
    
    for(int i{}; i < 9*9; ++i){
        if(matrix[i].number_of_variants() == 0) return NOSULUTION;
        if(!matrix[i].is_solved) result = false;
    }
    
    if(result) return SOLVED;
    else return NOTSOLVED;
}