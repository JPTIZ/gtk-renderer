#include "shapes.h"

#include <iostream>

namespace rudolph {
namespace objects {

void Point::draw(RenderTarget& target) const {
    target.draw_point(point);
}

void Line::draw(RenderTarget& target) const {
    target.draw_line(_a, _b);
}

void Polygon::draw(RenderTarget& target) const {
    for (auto i = 0u; i < _points.size() - 1; ++i) {
        target.draw_line(_points[i], _points[i + 1]);
    }

    target.draw_line(_points.back(), _points.front());
}

}
}
