#include "Array2D.h"
#include "Sudoku.h"
#include <cstdlib>
#include <ctime>

void function( Array2D<Cell> & matrix){
    matrix[1].value = 5;
}


int main(){



    int arr[81];
    for(int i{}; i < 81; ++i){
        std::cin >> arr[i];
    }

    Sudoku sudoku;
    for(int i{}; i < 81; ++i){
        sudoku.field[i] = arr[i];
    }
    sudoku.render();
    sudoku.print();
    std::cout << '\n';
    Solver solver;
    sudoku.field = solver.solve(sudoku.field);
    sudoku.render();
    sudoku.print();

    return 0;
}