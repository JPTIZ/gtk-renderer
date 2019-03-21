#include "geometry.h"

namespace rudolph {
namespace geometry {

void Point::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->move_to(pos.x, pos.y);
    cr->arc(pos.x, pos.y, 3, 0, 2 * M_PI);
}

void Line::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->move_to(a.x, a.y);
    cr->line_to(b.x, b.y);
}

void Polygon::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    auto start = vertices[0];
    cr->move_to(start.x, start.y);
    for (auto i = 1u; i < vertices.size(); i++) {
        auto next = vertices[i];
        cr->line_to(next.x, next.y);
        cr->move_to(next.x, next.y);
    }
    cr->line_to(start.x, start.y);
}

}
}
