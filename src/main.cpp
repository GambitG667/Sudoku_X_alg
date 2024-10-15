#include "Array2D.h"
#include "Sudoku.h"
#include <cstdlib>
#include <ctime>
#include "Matrix.h"

void function( Array2D<Cell> & matrix){
    matrix[1].value = 5;
}


int main(){

    int arr1[4] = {1, 0, 1, 0};
    int arr2[4] = {0, 1, 0, 1};
    int arr3[4] = {0, 1, 1, 1};
    int arr4[4] = {1, 1, 0, 0};

    Matrix m(4);
    m.add_string(arr1);
    m.add_string(arr2);
    m.add_string(arr3);
    m.add_string(arr4);

    AssociadetArray* colum;
    AssociadetArray* colum2;
    
    m.print();

    colum = m.colums_header;
    colum = colum->next;
    colum2 = colum->next;



    colum->remove();
    colum2->remove();

    m.print();

    colum2->recovery();
    colum->recovery();

    m.print();

    return 0;
}