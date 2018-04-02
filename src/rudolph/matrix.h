#ifndef RUDOLPH_MATRIX_H
#define RUDOLPH_MATRIX_H

#include <vector>

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

    Matrix operator*(const Matrix<T>& other)
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

    void to_string() {
        for (auto i = 0; i < height_; ++i) {
            for (auto j = 0; j < width_; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    const std::size_t width_, height_;
    std::vector<T> contents;
};

}

#endif
