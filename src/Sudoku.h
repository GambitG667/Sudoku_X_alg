#include "Array2D.h"


enum Mode{
    COLUM = 0,
    RAW = 1
};


class Sudoku{
private:
    Array2D<int> field;
    Array2D<char> screan;
    int height_screan;
    int width_screan;
public:
    Sudoku();
    ~Sudoku();
    void render();
    void print();
    void print_field();
    void write_line(int number, Mode mode, char fill);
    void swap(int number1, int number2, Mode mode);
    void swap_districts(int number1, int number2, Mode mode);
    void base_generate();
    void random_generate(int seed);
    void random_generate();

};