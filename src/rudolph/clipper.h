#ifndef RUDOLPH_CLIPPER_H
#define RUDOLPH_CLIPPER_H

#include "geometry.h"

#include <vector>

namespace rudolph {

enum class RegionCode {
    LEFT = 1,
    RIGHT = 2,
    UP = 4,
    DOWN = 8
};

enum class ClipMethod {
    COHEN_SUTHERLAND,
    LIANG_BARSKY
};

class Clipper {
    using Point2D = geometry::Point2D;
public:
    Clipper(ClipMethod method):
        _method{method}
    {}

    std::vector<Point2D> Clip(Point2D a, Point2D b);

private:
    ClipMethod _method;
    int region_code(Point2D p);
    std::vector<Point2D> cohen_sutherland(Point2D a, Point2D b);
    std::vector<Point2D> liang_barsky(Point2D a, Point2D b);

    const double edge_left = -1;
    const double edge_right = 1;
    const double edge_up = -1;
    const double edge_down = 1;
};

} // end namespace rudolph

#endif
