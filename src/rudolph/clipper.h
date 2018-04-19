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
    Clipper(ClipMethod method = ClipMethod::LIANG_BARSKY):
        _method{method}
    {}

    // Return false if point was not clipped (visible), true if clipped (hidden)
    bool clip_point(Point2D a);
    std::vector<Point2D> clip_line(Point2D a, Point2D b);
    std::vector<Point2D> clip_polygon(std::vector<Point2D>& points);
    void clip_pol_aux(Point2D a, Point2D b, std::vector<Point2D>& new_polygon, std::vector<Point2D>& intersections);

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
