#include "Sudoku.h"
#include "Game.h"
#include <iostream>
#include <random>
#include <vector>



void Game::main_loop(){
    int input{};
    while(true){
        std::cout << "-------------------\n";
        std::cout << "выберите один из вариантов:\n";
        std::cout << "1) сгенерировать судоку\n";
        std::cout << "2) решить судоку\n";
        std::cout << "3) выход\n";
        std::cout << ">>> ";
        std::cin >> input;
        if(input == 1) genegate_sudoku();
        else if (input == 2) solve_sudoku();
        else break;
    }


}

int Game::random_int(int min, int max){
    static std::mt19937 genegator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(genegator);
}


void Game::genegate_sudoku(){
    Sudoku sudoku;
    sudoku.base_generate();
    for(int i{}; i < 20; ++i) sudoku.random_generate();
    std::vector<int> variants_for_deleting(81);
    for(int i{}; i < 81; ++i) variants_for_deleting.at(i) = i;

    for(int i{}; i < 60;){
        int rand = random_int(0, variants_for_deleting.size()-1);
        int index = variants_for_deleting.at(rand);
        int value = sudoku.field[index];
        sudoku.field[index] = 0;
        if(Solver::solve_with_X_alg(sudoku.field).size() == 1){
            i += 1;
        }else{
            sudoku.field[index] = value;
        }
        variants_for_deleting.erase(variants_for_deleting.begin()+rand);
        if(variants_for_deleting.size() == 0){
            break;
        }
    }

    std::cout << "\n";
    sudoku.render();
    sudoku.print();
    std::cout << "\n";

    std::cout<<"Показать решение?\n1) да\n2) нет\n>>> ";
    int input{};
    std::cin >> input;
    if(input == 1){
        sudoku.field = Solver::solve_with_X_alg(sudoku.field).at(0);
        
        std::cout << "\n";
        sudoku.render();
        sudoku.print();
        std::cout << "\n";
    }
}

void Game::solve_sudoku(){

    Sudoku sudoku;

    std::cout << "Введите числа построчно, вместо пропусков ставте 0\n";
    for(int i{}; i < 81; ++i) std::cin >> sudoku.field[i];
    
    std::vector<Array2D<int>> result = Solver::solve_with_X_alg(sudoku.field);
    std::cout << "Найдено " << result.size() << " уникальных решений\n";
    std::cout << "1) вывести первое\n2) вывести все\n3) выход\n>>> ";
    int input{};
    std::cin >> input;
    if(input == 1){
        sudoku.field = result.at(0);
        sudoku.render();
        sudoku.print();
    }else if(input == 2){
        for(auto solution: Solver::solve_with_X_alg(sudoku.field)){
            sudoku.field = solution;
            std::cout<<'\n';
            sudoku.render();
            sudoku.print();
            std::cout<<'\n';
        }
    }
}

