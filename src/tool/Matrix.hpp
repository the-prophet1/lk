#ifndef LK_MATRIX_HPP
#define LK_MATRIX_HPP

#include <vector>

template<typename T>
class Matrix {
public:
    Matrix(T matrix[], int row, int column);

    Matrix();

    void Set(T matrix[], int row, int column);

    int ByteSize();

    const T *Data();

    int Column() const;

    int Row() const;

    const std::vector<T> &GetM();

    bool Empty();

private:
    std::vector<T> m;
    int row{};
    int column{};
};


template<typename T>
Matrix<T>::Matrix() = default;

template<typename T>
Matrix<T>::Matrix(T *matrix, int row, int column) {
    Set(matrix, row, column);
}

template<typename T>
int Matrix<T>::ByteSize() {
    return sizeof(T) * row * column;
}

template<typename T>
const T *Matrix<T>::Data() {
    return m.data();
}

template<typename T>
int Matrix<T>::Column() const {
    return column;
}

template<typename T>
int Matrix<T>::Row() const {
    return row;
}

template<typename T>
void Matrix<T>::Set(T *matrix, int r, int c) {
    row = r;
    column = c;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            m.push_back(matrix[i * c + j]);
        }
    }
}

template<typename T>
const std::vector<T> &Matrix<T>::GetM() {
    return m;
}

template<typename T>
bool Matrix<T>::Empty() {
    return m.empty();
}

#endif //LK_MATRIX_HPP
