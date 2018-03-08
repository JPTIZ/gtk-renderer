#include "shapes.h"

void Point::draw(RenderTarget& target) const {
    std::cout << "Drawing point in (" << location.x << ", " << location.y << ")\n";
}

void Line::draw(RenderTarget& target) const {
    //std::cout << "Drawing line in (" << _x << ", " << _y << ")\n";
}

void Polygon::draw(RenderTarget& target) const {
    //std::cout << "Drawing poly in (" << _x << ", " << _y << ")\n";
}
