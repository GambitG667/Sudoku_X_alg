#include "Array2D.h"
#include "Matrix.h"
#include <string>
#include <vector>
#pragma once
class AssociadetArray;

enum Mode{
    COLUM = 0,
    STR = 1
};


class Sudoku{
public:
    Array2D<int> field;
    Array2D<char> screan;
    int height_screan;
    int width_screan;

public:
    Sudoku();
    ~Sudoku();

    /*vusual methods*/

    void render();
    void print();
    void print_field();
    void write_line(int number, Mode mode, char fill);

    /*generative methods*/

    void swap(int number1, int number2, Mode mode);
    void swap_districts(int number1, int number2, Mode mode);
    void base_generate();
    void random_generate(int seed);
    void random_generate();

    /*solver's methods*/
    

};


struct Cadr{
    std::vector<AssociadetArray*> deleted_elements;
    Matrix* matrix;
    std::vector<AssociadetArray*> X;

    void print();
};


class Solver{
private:

public:

    static Cadr create_cadr(Matrix& matrix);
    static Cadr next_cadr(Matrix& matrix, Cadr& previus, std::vector<AssociadetArray*>& stack);
    static void reverse_cadr(Cadr& cadr);
    static std::vector<std::vector<AssociadetArray*>> X_algorithm(Matrix& matrix, std::vector<AssociadetArray*>& stack);
    static std::vector<Array2D<int>> solve_with_X_alg(Array2D<int> &field);
    static void create_character_vector(int index, int value, int* character_vector);

};