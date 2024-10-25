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

    sudoku.field = solver.solve_with_X_alg(sudoku.field);

    sudoku.render();
    sudoku.print();

    return 0;
}