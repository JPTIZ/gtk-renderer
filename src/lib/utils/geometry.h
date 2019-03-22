#ifndef RUDOLPH_UTILS_GEOMETRY_H
#define RUDOLPH_UTILS_GEOMETRY_H

#include <memory>

namespace rudolph {
namespace geometry {

struct Vec2{
    double x{0};
    double y{0};

    Vec2(double x_, double y_):
        x{x_},
        y{y_}
    {}

    Vec2 operator-() const {
        return Vec2{-x, -y};
    }

    Vec2& operator+=(const Vec2& v) {
        *this = Vec2{x + v.x, y + v.y};
        return *this;
    }

    Vec2& operator-=(const Vec2& v) {
        *this += -v;
        return *this;
    }

    Vec2& operator*=(double scalar) {
        *this = Vec2{x * scalar, y * scalar};
        return *this;
    }

    Vec2 operator+(const Vec2& v) const {
        auto result = *this;
        result += v;
        return result;
    }

    Vec2 operator-(const Vec2& v) {
        return *this + (-v);
    }

    Vec2 operator*(double scalar) {
        auto result = *this;
        result *= scalar;
        return result;
    }
};

struct Size {
    int width{0};
    int height{0};

    Size() = default;

    Size(int w, int h):
        width{w},
        height{h}
    {}
};

class Rectangle {
public:
    Rectangle(Vec2 pos, Size size):
        _pos{pos},
        _size{size}
    {}

    const Vec2& pos() const {
        return _pos;
    }

    Vec2& pos() {
        return _pos;
    }

    const Size& size() const {
        return _size;
    }

    Size& size() {
        return _size;
    }

    void offset(const Vec2& offset) {
        _pos += offset;
    }

    void move(const Vec2& destiny) {
        _pos = destiny;
    }

    void resize(const Size& new_size) {
        _size = new_size;
    }

private:
    Vec2 _pos;
    Size _size;
};

}
}

#endif
