#ifndef RUDOLPH_MATRIX_H
#define RUDOLPH_MATRIX_H

#include <vector>
#include <iostream>

namespace rudolph {

template <typename T>
class Matrix {
public:
    Matrix(std::size_t height, std::size_t width) :
        width_{width},
        height_{height},
        contents(width_*height_)
    {}

    Matrix(const Matrix &) = default;

    // Create a matrix (1 x n), n = vec.size()
    Matrix(std::vector<T> &vec, std::size_t height = 1, std::size_t width = 0):
        width_{ (width==0)?vec.size():width},
        height_{height},
        contents{vec}
    {}

    template <typename U>
    friend class Matrix;

    template <typename U>
    Matrix(const Matrix<U> &other) :
        width_{other.width_},
        height_{other.height_},
        contents{begin(other.contents), end(other.contents)}
    {}

    const T &operator()(std::size_t i, std::size_t j) const
    {
        return contents[i*width_ + j];
    }

    T &operator()(std::size_t i, std::size_t j)
    {
        return contents[i*width_ + j];
    }

    template <typename U>
    Matrix operator*(const Matrix<U>& other)
    {
        std::size_t height = this->height();
        std::size_t width = other.width();
        Matrix product(height, width);
        for (auto i = 0; i < height; ++i) {
            for (auto j = 0; j < width; ++j) {
                for (auto inner = 0; inner < this->width(); ++inner) {
                    product(i, j) += (*this)(i, inner) * other(inner, j);
                }
            }
        }
        return product;
    }

    std::size_t width() const
    {
        return width_;
    }

    void width(std::size_t w) {
        width_ = w;
    }

    void height(std::size_t h) {
        height_ = h;
    }

    std::size_t height() const
    {
        return height_;
    }

    std::size_t size() const
    {
        return contents.size();
    }

    const T* data() const {
        return contents.data();
    }

    T* data() {
        return contents.data();
    }

    void to_string() const {
        for (auto i = 0; i < height_; ++i) {
            for (auto j = 0; j < width_; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    std::size_t width_, height_;
    std::vector<T> contents;
};

}

#endif
