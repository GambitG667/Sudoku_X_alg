#ifndef ARRAY2D
#define ARRAY2D


class Array2D{
private:
    int* array;
    int width, height;
public:
    Array2D(const int x,const int y);
    ~Array2D();
    void printArray();
    void pprintArray(int number_digits);
    int& operator()(const int x, const int y);

};


#endif