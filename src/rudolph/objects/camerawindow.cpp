#include "camerawindow.h"

namespace rudolph {

void CameraWindow::move(double dx, double dy) {
    auto d = Point2D{dx, dy};

    _bottom_left += d;
    _top_right += d;
}

void CameraWindow::zoom(double step) {
    auto d = (_top_right - _bottom_left) * (step / 2);

    _bottom_left -= d;
    _top_right += d;
}

void CameraWindow::set_width(int width) {
    _top_right.x() = _bottom_left.x() + width;
}

void CameraWindow::set_height(int height) {
    _top_right.y() = _bottom_left.y() + height;
}

}
