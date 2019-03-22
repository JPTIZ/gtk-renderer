#ifndef RUDOLPH_RENDER_VIEWPORT_H
#define RUDOLPH_RENDER_VIEWPORT_H

#include "../algebra/matrix.h"
#include "../render/graphic_object.h"
#include "../utils/geometry.h"

namespace rudolph {
namespace render {

class Viewport: public rudolph::geometry::Rectangle, GraphicalObject {
    using Vec2 = rudolph::geometry::Vec2;
    using Size = rudolph::geometry::Size;
public:
    Viewport(Vec2 pos, Size size):
        Rectangle{pos, size}
    {}

    void draw() override;
};

}
}

#endif
