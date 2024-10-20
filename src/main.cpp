#include "Array2D.h"
#include "Sudoku.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Matrix.h"

void function( Array2D<Cell> & matrix){
    matrix[1].value = 5;
}


int main(){

    int arr1[5] = {1, 1, 0, 0, 0};
    int arr2[5] = {0, 1, 1, 0, 0};
    int arr3[5] = {1, 0, 0, 0, 1};
    int arr4[5] = {1, 0, 0, 1, 0};
    int arr5[5] = {0, 0, 0, 0, 1};

    Matrix m(5);
    m.add_string(arr1);
    m.add_string(arr2);
    m.add_string(arr3);
    m.add_string(arr4);
    m.add_string(arr5);

    std::vector<AssociadetArray*> stack;

    //std::cout<<'\n'<<m.colums_header->lenth_chain() << ' ' << m.string_header->lenth_chain() << '\n';

    Solver solver;
    solver.X_algorithm(m, stack);

    std::cout << "X algorithm passed\n";
    
    std::cout << std::endl;
    for(auto i: stack) std::cout << i->index << " ";
    std::cout << std::endl;

    return 0;
}