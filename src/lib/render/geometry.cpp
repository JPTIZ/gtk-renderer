#include "geometry.h"

namespace rudolph {
namespace geometry {

void Point::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->move_to(this->pos.x, this->pos.y);
    cr->arc(this->pos.x, this->pos.y, 3, 0, 2 * M_PI);
}

void Line::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->move_to(this->a.x, this->a.y);
    cr->line_to(this->b.x, this->b.y);
}

void Polygon::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    Vec2 start = this->vertices[0];
    cr->move_to(start.x, start.y);
    for(int i = 1; i < this->vertices.size(); i++) {
        Vec2 next = this->vertices[i];
        cr->line_to(next.x, next.y);
        cr->move_to(next.x, next.y);
    }
    cr->line_to(start.x, start.y);
}

}
}