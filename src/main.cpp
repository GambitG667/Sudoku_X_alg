#include "Array2D.h"
#include "Sudoku.h"
#include <cstdlib>
#include <ctime>




int main(){

    Sudoku sudoku;
    Solver solver;

    for(int i{}; i < 81; ++i){
        std::cin >> sudoku.field[i];
    }

    sudoku.render();
    sudoku.print();

    for(auto sulution:solver.solve_with_X_alg(sudoku.field)){
        std::cout<< "\n------------------------------------\n";
        sudoku.field = sulution;
        sudoku.render();
        sudoku.print();
    }
    return 0;
}