#ifndef LK_MATRIX_H
#define LK_MATRIX_H

#include <vector>

class Matrix {
public:
    Matrix(float matrix, int row,int column);

private:
    std::vector<float> vec;
};


#endif //LK_MATRIX_H
