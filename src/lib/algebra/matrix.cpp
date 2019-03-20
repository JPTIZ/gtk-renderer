#include "matrix.h"

namespace rudolph {
namespace algebra {

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m) {
    auto this_it = _data.begin();

    for (const auto& v: m) {
        *this_it += v;
        ++this_it;
    }

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m) {
    if (width() != m.height() and
        height() != m.width()) {
        throw MatrixArithError{*this, m};
    }

    auto result = Matrix<T>{m.width(), m.height()};

    for (auto y = 0; y < m.height(); ++y) {
        for (auto x = 0; x < m.width(); ++x) {
            result += _data[y][x] * m._data[x][y];
        }
    }

    *this = result;
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(int s) {
    for (auto& v: _data) {
        v += s;
    }

    return *this;
}

}
}
