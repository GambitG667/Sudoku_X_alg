#include "Matrix.h"
#include "Array2D.h"

class AssociadetArray;


Node* Colum::push_back(){
    if(first == nullptr){
        first = new Node();
        last = first;
    }else{
        Node* node = new Node();
        last->down = node;
        node->top = last;
        last = node;
    }

    last->head_top = this;
    return last;
}

void Colum::push_back(Node* node){
    if(first == nullptr){
        first = node;
        last = first;
    }else{
        last->down = node;
        node->top = last;
        last = node;
        node->head_top = this;
    }
    last->head_top = this;
}


void Colum::remove(){
    if(previus != nullptr) previus -> next = next;
    if(next != nullptr) next -> previus = previus;
    if(previus == nullptr) matrix->colums_header = next;
    Node* ptr = first;
    while(ptr != nullptr){
        if(ptr->right != nullptr) ptr->right->left = ptr->left;
        if(ptr->left != nullptr) ptr->left->right = ptr->right;
        if(ptr->left == nullptr) ptr->head_left->first = ptr->right;
        ptr = ptr->down;
    }
}

void Colum::recovery(){
    if(previus != nullptr) previus -> next = this;
    if(next != nullptr) next -> previus = this;
    if(previus == nullptr) matrix->colums_header = this;
    Node* ptr = first;
    while(ptr != nullptr){
        if(ptr->right != nullptr) ptr->right->left = ptr;
        if(ptr->left != nullptr) ptr->left->right = ptr;
        if(ptr->left == nullptr) ptr->head_left->first = ptr;
        ptr = ptr->down;
    }
}

int Colum::size(){
    int result{0};

    Node* ptr = first;
    while(ptr != nullptr){
        ++result;
        ptr = ptr->down;
    }

    return result;
}   

int Colum::lenth_chain(){
    int result{};
    AssociadetArray * ptr = this;
    while(ptr != nullptr){
        ++result;
        ptr = ptr->next;
    }
    return result;
}

Colum::~Colum(){
    Node* ptr = last;
    while(ptr->top != nullptr){
        ptr = ptr->top;
        delete ptr->down;
    }
    delete ptr;
}


Node* String::push_back(){
    if(first == nullptr){
        first = new Node();
        last = first;
    }else{
        Node* node = new Node();
        last->right = node;
        node->left = last;
        last = node;
    }

    last->head_left = this;
    return last;
}

void String::push_back(Node* node){
    if(first == nullptr){
        first = node;
        last = first;
    }else{
        last->right = node;
        node->left = last;
        last = node;
    }
    last->head_left = this;
}

void String::remove(){
    if(previus != nullptr) previus -> next = next;
    if(next != nullptr) next -> previus = previus;
    if(previus == nullptr) matrix->string_header = next;
    Node* ptr = first;
    while(ptr != nullptr){
        if(ptr->top != nullptr) ptr->top->down = ptr->down;
        if(ptr->down != nullptr) ptr->down->top = ptr->top;
        if(ptr->top == nullptr) ptr->head_top->first = ptr->down;
        ptr = ptr->right;
    }
}

void String::recovery(){
    if(previus != nullptr) previus -> next = this;
    if(next != nullptr) next -> previus = this;
    if(previus == nullptr) matrix->string_header = this;
    Node* ptr = first;
    while(ptr != nullptr){
        if(ptr->top != nullptr) ptr->top->down = ptr;
        if(ptr->down != nullptr) ptr->down->top = ptr;
        if(ptr->top == nullptr) ptr->head_top->first = ptr;
        ptr = ptr->right;
    }
}

int String::size(){
    int result{0};

    Node* ptr = first;
    while(ptr != nullptr){
        ++result;
        ptr = ptr->right;
    }

    return result;
}  

int String::lenth_chain(){
    int result{};
    AssociadetArray * ptr = this;
    while(ptr != nullptr){
        ++result;
        ptr = ptr->next;
    }
    return result;
}

Matrix::Matrix(int len){
    number_colums = len;
    set_colums(len);
}

Matrix::~Matrix(){
    AssociadetArray* ptr = last_colum;

    while(ptr->previus != nullptr){
        ptr = ptr->previus;
        delete ptr->next;
    }
    delete ptr;

    ptr = last_string;
    while(ptr->previus != nullptr){
        ptr = ptr->previus;
        delete ptr->next;
    }
    delete ptr;
}

void Matrix::set_colums(int len){
    colums_header = new Colum(0);
    colums_header->matrix = this;
    AssociadetArray *ptr = colums_header;
    for(int i{1}; i < len; ++i){
        Colum* colum = new Colum(i);
        colum->matrix = this;
        ptr->next = colum;
        colum->previus = ptr;
        ptr = colum;
        last_colum = ptr;
    }
}

void Matrix::add_string(int* array){
    if(string_header == nullptr){
        string_header = new String(0);
        last_string = string_header;
        string_header->matrix = this;
    }else{
        String* new_str = new String(last_string->index+1);
        new_str->matrix = this;
        last_string->next = new_str;
        new_str -> previus = last_string;
        last_string = new_str;
    }
    AssociadetArray* colum = colums_header;
    AssociadetArray* string = last_string;
    for(int i{}; colum != nullptr; ++i){
        if(array[i] == 0){
            colum = colum->next;
            continue;
        }
        string->push_back(colum->push_back());
        colum = colum->next;
    }
}

void Matrix::print(){
    Array2D<int> screan(number_colums, last_string->index+1);
    screan.fill(0);
    AssociadetArray* string = string_header;
    while (string != nullptr) {
        Node* node = string->first;
        while (node != nullptr) {
            screan(node->head_top->index, string->index) = 1;
            node = node->right;
        }
        string = string->next;    
    }
    screan.printArray();
    std::cout<<std::endl;
}

int Matrix::count_colums(){
    int result = 0;
    AssociadetArray* ptr = colums_header;
    while(ptr !=0){
        ++result;
        ptr = ptr->next;
    }
    return result;
}

int Matrix::count_strings(){
    int result = 0;
    AssociadetArray* ptr = string_header;
    while(ptr !=0){
        ++result;
        ptr = ptr->next;
    }
    return result;
}