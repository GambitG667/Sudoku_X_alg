#include "Sudoku.h"
#include "Array2D.h"
#include "Matrix.h"
#include <iostream>
#include <vector>
#include <set>





Sudoku::Sudoku(): field(9,9), screan(35, 17) {
    field.fill(7);
    screan.fill(' ');
    
    height_screan = 17;
    width_screan = 35;
}
Sudoku::~Sudoku(){};
void Sudoku::render(){
    char sep_v = '|';
    char sep_g = '-';
    char m_sep = '#';

    for(int i{1}; i < 17; i += 2) write_line(i, STR, sep_g);
    for(int i{3}; i < 35; i += 4) write_line(i, COLUM, sep_v);
    for(int i{11}; i < 35; i += 12) write_line(i, COLUM, m_sep);
    for(int i{5}; i < 17; i += 6) write_line(i, STR, m_sep);
    for(int j{}, y{}; y < 9; j += 2, ++y) 
        for( int i{1}, x{}; x < 9; i += 4, ++x) 
            screan(i,j) = static_cast<char>('0'+field(x, y));
}

void Sudoku::print(){
    for(int j{}; j < height_screan; ++j){

        for(int i{}; i<width_screan; ++i) std::cout<< screan(i, j);
        
        std::cout << '\n';
    }
    

}

void Sudoku::print_field(){
    field.printArray();
}

void Sudoku::write_line(int number, Mode mode, char fill){
    if(mode == COLUM){
        for(int i{}; i < height_screan; ++i){
            screan(number, i) = fill;
        }
    }else{
        for(int i{}; i < width_screan; ++i){
            screan(i, number) = fill;
        }
    }
}

void Sudoku::swap(int number1, int number2, Mode mode){
    int bufer{};
    if(mode==COLUM){
        for(int i{}; i < 9; ++i){
            bufer = field(number1, i);
            field(number1, i) = field(number2, i);
            field(number2, i) = bufer;
        }
    }else{
        for(int i{}; i < 9; ++i){
            bufer = field(i, number1);
            field(i, number1) = field(i, number2);
            field(i, number2) = bufer;
        }
    }
}

void Sudoku::swap_districts(int number1, int number2, Mode mode){
        for(int i{}; i < 3; ++i){
            swap(i+number1*3, i+number2*3, mode);
        }
}

void Sudoku::base_generate(){
    int nat_num[9]={1,2,3,4,5,6,7,8,9};

    for(int district{0}; district < 3; ++district){
        for(int j{}; j < 3; ++j){
            for(int i{}; i < 9; ++i){
                field(i, j+3*district) = nat_num[(i+3*j+district)%9];
            }
        }
    }
}

void Sudoku::random_generate(int seed){
    if(seed % 10 > 5){

        int number_district = seed%7%3;
        
        int number1{seed%3};
        int number2{seed%5%3};
        number2 = number2 == number1 ?  (number2+1) % 3 : number2;
        number1 += number_district*3;
        number2 += number_district*3;
        swap(number1, number2, Mode(seed%2));

    }else{
        int number1 = seed % 3;
        int number2 = seed % 5 % 3;
        number2 = number2 == number1 ?  (number2+1) % 3 : number2;

        swap_districts(number1, number2, Mode(seed%2));
    }
}

void Sudoku::random_generate(){
    
    
    if(rand() % 2 == 1){

        int number_district = rand()%3;
        
        int number1{rand()%3};
        int number2{rand()%3};
        number2 = number2 == number1 ?  (number2+1) % 3 : number2;
        number1 += number_district*3;
        number2 += number_district*3;
        swap(number1, number2, Mode(rand()%2));

    }else{
        int number1 = rand() % 3;
        int number2 = rand() % 3;
        number2 = number2 == number1 ?  (number2+1) % 3 : number2;

        swap_districts(number1, number2, Mode(rand()%2));
    }
}    


Cadr Solver::create_cadr(Matrix& matrix){
    Cadr result;
    result.matrix = &matrix;

    AssociadetArray * s = matrix.colums_header;
    if(s == nullptr) return result;
    int size_s = s->size();
    AssociadetArray* ptr = matrix.colums_header;

    while(ptr != nullptr){
        if(size_s > ptr->size()){
            s = ptr;
            size_s = s->size();
        }
        ptr = ptr->next;
    }
    Node* node_ptr = s->first;
    while (node_ptr != nullptr){
        result.X.push_back(node_ptr->head_left);
        node_ptr = node_ptr->down;
    }
    return result;

}

Cadr Solver::next_cadr(Matrix& matrix, Cadr& previus, std::vector<AssociadetArray*>& stack){
    std::vector<AssociadetArray*> remuved_elements;
    stack.push_back(previus.X.back());
    previus.X.pop_back();
    std::set<AssociadetArray*> colums;
    std::set<AssociadetArray*> strings;

    Node* node_ptr = stack.back()->first;

    while(node_ptr != nullptr){
        colums.insert(node_ptr->head_top);
        node_ptr = node_ptr->right;
    }
    for(auto colum:colums){
        node_ptr = colum->first;
        while (node_ptr != nullptr) {
            strings.insert(node_ptr->head_left);
            node_ptr = node_ptr->down;
        }
    }

    for(auto colum:colums){
        colum->remove();
        remuved_elements.push_back(colum);
    }
    for(auto string:strings){
        string->remove();
        remuved_elements.push_back(string);
    }

    Cadr result = create_cadr(matrix);
    result.deleted_elements = remuved_elements;
    return result;
}

void Solver::reverse_cadr(Cadr& cadr){
    for(int i=cadr.deleted_elements.size()-1; i >= 0; --i){
        cadr.deleted_elements.at(i)->recovery();
    }
}

std::vector<std::vector<AssociadetArray*>> Solver::X_algorithm(Matrix& matrix, std::vector<AssociadetArray*>& stack){
    std::vector<std::vector<AssociadetArray*>> ansvers;
    
    std::vector<Cadr> cadrs;
    int index = 0;
    cadrs.push_back(create_cadr(matrix));

    while(true){
        if(index < 0) break;

        if(matrix.count_colums() == 0){
            ansvers.push_back(stack);
            reverse_cadr(cadrs.at(index));
            cadrs.pop_back();
            --index;
            stack.pop_back();
            continue;
        }

        if(matrix.count_strings() == 0){
            reverse_cadr(cadrs.at(index));
            cadrs.pop_back();
            --index;
            stack.pop_back();
            continue;
        }
        if(cadrs.at(index).X.empty()){
            reverse_cadr(cadrs.at(index));
            cadrs.pop_back();
            --index;
            stack.pop_back();
            continue;
        }
        cadrs.push_back(next_cadr(matrix, cadrs.at(index), stack));
        ++index;
    }

    while(index > 0){
        reverse_cadr(cadrs.at(index));
        cadrs.pop_back();
        --index;
    }

    return ansvers;
}


void Cadr::print(){
    std::cout << "---------------\n";
    for(auto i: deleted_elements) std::cout<<i->index << ' ';
    std::cout << '\n';
    for(auto i: X) std::cout<<i->index << ' ';
    std::cout << '\n';
    std::cout << "---------------\n";
}

std::vector<Array2D<int>> Solver::solve_with_X_alg(Array2D<int> &field){
    Matrix matrix(4*9*9);
    std::vector<AssociadetArray*> stack;
    std::vector<Array2D<int>> result;
    
    for(int index{}; index < 81; ++index){
        if(field[index] != 0){
            int character_vector[4*9*9] = {0};
            create_character_vector(index, field[index], character_vector);
            matrix.add_string(character_vector);
        }else{
            for(int value{1}; value <= 9; ++value){
                int character_vector[4*9*9] = {0};
                create_character_vector(index, value, character_vector);
                matrix.add_string(character_vector);
            }
        }
    }
    std::vector<std::vector<AssociadetArray*>> ansvers;

    ansvers = X_algorithm(matrix, stack);

    for(auto ansver: ansvers){
        Array2D<int> field(9, 9);
        for(auto string:ansver){
            int index = string->first->head_top->index;                   // декодирование индекса
            int value = (string->first->right->head_top->index - 81) / 9 + 1; // декодирование значения

        field[index] = value;
        }
        result.push_back(field);
    }

    return result;
}

void Solver::create_character_vector(int index, int value, int* character_vector){
    /*
    1) в каждой клетке по цифре
    2) в каждой строке каждое число встречается один раз
    3) в каждом столбце каждое число встречается один раз
    4) в каждом квадранте каждое число всречается один раз
    
    character vector = [<81: число в клетке><9*<9:число в строке>><9*<9:число в столбце>><9*<9:число в квадранте>>]
    
    число n в клетке x:
    i строка = x / 9
    j столбец = x % 9
    k квадрант = i / 3 * 3 + j / 3

    character_vector[x] = 1 <81: число в клетке>
    character_vector[81+9*(n-1)+j] = 1 <9*<9:число в строке>
    character_vector[162+9*(n-1)+i] = 1 <9*<9: число в столбце>>
    character_vector[243+9*(n-1)+k)] = 1 <9*<9: число в квадранте>>
    */

    int i = index/9;          // строка
    int j = index%9;          // столбец
    int k = i/3*3 + j/3;      // квадрант

    character_vector[index] = 1;                 // <81: число в клетке>
    character_vector[81+9*(value-1)+i] = 1;  // <9*<9:число в строке>
    character_vector[162+9*(value-1)+j] = 1; // <9*<9:число в столбце>
    character_vector[243+9*(value-1)+k] = 1; // <9*<9:число в квадранте>
}