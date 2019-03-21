#ifndef TOTALLY_A_STUB_H
#define TOTALLY_A_STUB_H

#include <string>

namespace rudolph {
namespace geometry {

/**
 * TODO: Remove after merging Vina's changes.
 */
struct Vec2 {
    int x;
    int y;

    Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
    Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
};

struct Size {
    int width;
    int height;
};

}

class GraphicalObject {
    std::string _name;
    std::string _type;
    virtual void draw() = 0;
};
}

#endif