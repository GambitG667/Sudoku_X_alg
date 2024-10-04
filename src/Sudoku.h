#include "Array2D.h"


enum Mode{
    COLUM = 0,
    RAW = 1
};

enum Status{
    NOTSOLVED = 0,
    SOLVED = 1,
    NOSULUTION = -1
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

struct Cell{
    bool is_solved = false;
    int value = 0;
    int character_vector[10]={0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    int number_of_variants();
};


class Solver{
private:

public:

    void check_variants(Array2D<Cell> &matrix);
    Array2D<int> solve( Array2D<int> field);
    Status is_solved(Array2D<Cell> & matrix);
};