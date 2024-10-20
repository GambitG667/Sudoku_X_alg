#include <vector>
#include <iostream>
#pragma once
class AssociadetArray;
class Colum;
class String;
class Matrix;


struct Node{
    AssociadetArray* head_left = nullptr;
    AssociadetArray* head_top = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* top = nullptr;
    Node* down = nullptr;
};

class AssociadetArray{
public:
    int index;
    bool is_on=true;
    Node*  first=nullptr;
    Node* last=nullptr;
    AssociadetArray* previus=nullptr;
    AssociadetArray* next=nullptr;
    Matrix* matrix = nullptr;

    AssociadetArray(int index):index(index){};
    virtual ~AssociadetArray(){};
    virtual Node* push_back()=0;
    virtual void  push_back(Node* node)=0;
    virtual void  remove()=0;
    virtual void  recovery()=0;
    virtual int   size()=0;
    virtual int   lenth_chain()=0;
};

class Colum: public AssociadetArray{
public:
    Node* push_back() override;
    void  push_back(Node* node) override;
    void  remove() override;
    void  recovery() override;
    int   size() override;
    int   lenth_chain() override;
    Colum(int index):AssociadetArray(index){}
    ~Colum();
};

class String: public AssociadetArray{
public:
    Node* push_back() override;
    void push_back(Node* node) override;
    void remove() override;
    void recovery() override;
    int   size() override;
    int   lenth_chain() override;
    String(int index):AssociadetArray(index){}
};

class Matrix{
public:
    int number_colums;
    AssociadetArray* colums_header=nullptr;
    AssociadetArray* string_header=nullptr;
    AssociadetArray* last_colum=nullptr;
    AssociadetArray* last_string=nullptr;

    Matrix(int len);
    ~Matrix();
    
    void set_colums(int len);
    void add_string(int* array);
    int count_colums();
    int count_strings();
    void print();
};