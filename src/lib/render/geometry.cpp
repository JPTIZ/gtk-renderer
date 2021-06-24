#include "geometry.h"

#include <iostream>

namespace {

using rudolph::geometry::Vec2;
using rudolph::render::Window;

auto to_window(const Vec2& point, const Window& window) {
    auto [win_x, win_y] = window.pos();
    return Vec2{ point.x - win_x, point.y - win_y };
}
}

namespace rudolph {
namespace geometry {

void Point::draw(const Cairo::RefPtr<Cairo::Context>& cr, const Window& window) {
    auto _pos = to_window(pos, window);
    cr->move_to(_pos.x, _pos.y);
    cr->arc(_pos.x, _pos.y, 3, 0, 2 * M_PI);
}

void Line::draw(const Cairo::RefPtr<Cairo::Context>& cr, const Window& window) {
    (void)window;
    auto [a_x, a_y] = to_window(a, window);
    auto [b_x, b_y] = to_window(b, window);
    cr->move_to(a_x, a_y);
    cr->line_to(b_x, b_y);
}

void Polygon::draw(const Cairo::RefPtr<Cairo::Context>& cr, const Window& window) {
    auto start = to_window(vertices[0], window);
    cr->move_to(start.x, start.y);
    for (auto i = 1u; i < vertices.size(); i++) {
        auto next = to_window(vertices[i], window);
        cr->line_to(next.x, next.y);
        cr->move_to(next.x, next.y);
    }
    cr->line_to(start.x, start.y);
}

}
}
