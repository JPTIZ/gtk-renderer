#ifndef RUDOLPH_VIEWPORT_H
#define RUDOLPH_VIEWPORT_H

#include <iostream>

#include "../geometry.h"

namespace rudolph {

class Viewport {
    using Point2D = geometry::Point;
public:
    Viewport(Point2D top_left, Point2D bottom_right):
        _top_left{top_left},
        _bottom_right{bottom_right}
    {}

    Viewport(geometry::Size size):
        _top_left{0, 0},
        _bottom_right{size.width, size.height}
    {}

    Point2D top_left() const {
        return _top_left;
    }

    Point2D bottom_right() const {
        return _bottom_right;
    }

    int width() const {
        return (_bottom_right.x - _top_left.x);
    }

    int height() const {
        return (_bottom_right.y - _top_left.y);
    }

    void set_width(int width) {
        _bottom_right.x = _top_left.x + width;
    }

    void set_height(int height) {
        _bottom_right.y = _top_left.y + height;
    }

    void resize(int width, int height) {
        set_width(width);
        set_height(height);
    }

  private:
    Point2D _top_left;
    Point2D _bottom_right;
};

}

#endif
