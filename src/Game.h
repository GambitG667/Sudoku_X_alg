#include "Sudoku.h"
#pragma once

class Game{
private:
    Sudoku sudoku;

public:

    static void main_loop();
    static void genegate_sudoku();
    static void solve_sudoku();
    static int random_int(int min, int max);


};