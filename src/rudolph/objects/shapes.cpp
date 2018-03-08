#include "shapes.h"

#include <iostream>

namespace rudolph {
namespace objects {

void Point::draw(RenderTarget& target) const {
    std::cout << "Drawing point in (" << point.x << ", " << point.y << ")\n";
    target.draw_point(point);
}

void Line::draw(RenderTarget& target) const {
    //std::cout << "Drawing line in (" << _a.x << ", " << _a.y << ", " << _y << ")\n";
    target.draw_line(_a, _b);
}

void Polygon::draw(RenderTarget& target) const {
    //std::cout << "Drawing poly in (" << _x << ", " << _y << ")\n";
    for (auto i = 0u; i < _points.size() - 1; ++i) {
        target.draw_line(_points[i], _points[i + 1]);
    }

    target.draw_line(_points.back(), _points.front());
}

}
}
