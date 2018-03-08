#ifndef RUDOLPH_RENDER_H
#define RUDOLPH_RENDER_H

namespace rudolph {
namespace render {

/**
 * Drawable canvas.
 *
 * Abstracts the idea of an output drawing target.
 */
class RenderTarget {
};

/**
 * Manages drawable components and applies window/viewport transformations.
 */
class Renderer {
public:
    void refresh();
};

/**
 * Drawable components' interface
 */
class Drawable {
public:
    virtual void draw(RenderTarget&) const = 0;
};

}
}
#endif
