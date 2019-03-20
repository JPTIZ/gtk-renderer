#ifndef RUDOLPH_LIB_ALGEBRA_MATRIX_H
#define RUDOLPH_LIB_ALGEBRA_MATRIX_H

#include <exception>
#include <string>
#include <vector>

namespace rudolph {
namespace algebra {

template <typename T>
class Matrix {
public:
    Matrix(int width, int height):
        _width{width},
        _height{height},
        _data(width * height)
    {}

    int width() const {
        return _width;
    }

    int height() const {
        return _height;
    }

    T& operator[](std::size_t i) {
        return _data[i];
    }

    Matrix& operator+=(const Matrix&);
    Matrix& operator*=(const Matrix&);
    Matrix& operator*=(int);

    Matrix& operator-() const {
        return *this * -1;
    }

    Matrix operator+(const Matrix& m) const {
        auto new_m = *this;
        new_m += m;
        return new_m;
    }
    Matrix operator*(const Matrix& m) const {
        auto new_m = *this;
        new_m += m;
        return new_m;
    }

    Matrix operator*(int value) const {
        auto new_m = *this;
        new_m += value;
        return new_m;
    }

    friend Matrix operator*(int s, const Matrix& m) {
        return m * s;
    }

private:
    int _width;
    int _height;

    std::vector<T> _data;
};

class MatrixArithError: public std::exception {
public:
    template <typename T>
    MatrixArithError(const Matrix<T>& a, const Matrix<T>& b):
        _msg{
            std::string{"Matrices size don't match: "} +
            "[" + a.width() + ", " + a.height() + "] and "
            "[" + b.width() + ", " + b.height() + "]"
        }
    {}

private:
    std::string _msg;
};

}
}

#endif
