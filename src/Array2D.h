#pragma once


class Array2D{
private:
    int* array;
    int width, height;
    void writeLine(int lenth, char simbol, char separator1, char separator2);
public:
    Array2D(const int x,const int y);
    ~Array2D();
    void printArray();
    void pprintArray();
    int& operator()(const int x, const int y);

};

