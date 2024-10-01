#include "Array2D.h"


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
    void write_line(int number, bool is_vertical, char fill);



};