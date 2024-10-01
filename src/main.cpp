#include "Sudoku.h"
#include <cstdlib>
#include <ctime>

int main(){

    srand(static_cast<unsigned int>(time(0)));

    Sudoku sudoku;
    sudoku.base_generate();
    for(int i{}; i < 50; ++i){
        sudoku.random_generate();
    }
    sudoku.render();
    sudoku.print();


    return 0;
}