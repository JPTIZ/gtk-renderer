#ifndef RUDOLPH_CAMERA_H
#define RUDOLPH_CAMERA_H

#include "../geometry.h"

namespace rudolph {

class CameraWindow {
    using Point2D = geometry::Point;
public:
    CameraWindow():
        _bottom_left{Point2D{0, 0}},
        _top_right{Point2D{200, 100}}
    {}

    CameraWindow(Point2D bottom_left, Point2D top_right):
        _bottom_left{bottom_left},
        _top_right{top_right}
    {}

    Point2D bottom_left() const {
        return _bottom_left;
    }

    Point2D top_right() const {
        return _top_right;
    }

    void move(int dx, int dy);
    void zoom(double step);
    void set_width(int width);
    void set_height(int height);

  private:
    Point2D _bottom_left;
    Point2D _top_right;
};

}

#endif
