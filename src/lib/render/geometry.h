#ifndef RUDOLPH_RENDER_GEOMETRY_H
#define RUDOLPH_RENDER_GEOMETRY_H

#include <memory>
#include <vector>
#include "graphic_object.h"
#include "../utils/geometry.h"

namespace rudolph {
namespace geometry {

struct Point : GraphicObject {
    Vec2 pos;

    Point() = default;

    Point(Vec2 pos_):
        pos{pos_}
    {}

    Point(double x_, double y_):
        Point(Vec2(x_, y_))
    {}

    void draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

struct Line : GraphicObject {
    Vec2 a;
    Vec2 b;

    Line() = default;

    Line(Vec2 a_, Vec2 b_):
        a{a_},
        b{b_}
    {}

    void draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

struct Polygon : GraphicObject {
    std::vector<Vec2> vertices;

    Polygon(std::vector<Vec2> vertices_):
        vertices{vertices_}
    {}

    void draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

}
}


#endif
