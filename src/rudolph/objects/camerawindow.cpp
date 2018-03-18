#include "camerawindow.h"

namespace rudolph {

void CameraWindow::move(int dx, int dy) {
    _bottom_left.x += dx;
    _bottom_left.y += dy;
    _top_right.x += dx;
    _top_right.y += dy;
}

void CameraWindow::zoom(double step) {
    int dx = (_top_right.x - _bottom_left.x) * step / 2;
    int dy = (_top_right.y - _bottom_left.y) * step / 2;
    _bottom_left.x -= dx;
    _bottom_left.y -= dy;
    _top_right.x += dx;
    _top_right.y += dy;
}

void CameraWindow::set_width(int width) {
    _top_right.x = _bottom_left.x + width;
}

void CameraWindow::set_height(int height) {
    _top_right.y = _bottom_left.y + height;
}

}