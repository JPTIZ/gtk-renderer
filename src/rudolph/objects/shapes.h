#ifndef RUDOLPH_OBJECTS_SHAPES_H
#define RUDOLPH_OBJECTS_SHAPES_H

#include "../rudolph/render.h"

namespace rudolph::objects {

class Point: render::Drawable {
public:
    void draw(render::RenderTarget&) const override;
};

class Line: render::Drawable {
public:
    void draw(render::RenderTarget&) const override;
};

class Polygon: render::Drawable {
public:
    void draw(render::RenderTarget&) const override;
};

}

#endif
