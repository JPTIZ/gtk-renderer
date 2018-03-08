#ifndef RUDOLPH_RENDER_H
#define RUDOLPH_RENDER_H

#include <memory>
#include <vector>

#include "../utils.h"

namespace rudolph {

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

    template <typename T>
    void add_object(T x) {
        objects.push_back(std::make_unique<Drawable<T>>(x));
    }

private:
    /**
     * Drawable components' interface
     */
    struct IDrawable {
        virtual ~IDrawable() = default;
        virtual std::unique_ptr<IDrawable> copy() const = 0;
        virtual void draw(RenderTarget&) const = 0;
    };

    template <typename T>
    struct Drawable: IDrawable {
        Drawable(T x):
            x{x}
        {}

        std::unique_ptr<IDrawable> copy() const override {
            return std::make_unique<Drawable>(*this);
        }

        T x;
    };

    RenderTarget target;
    std::vector<std::unique_ptr<IDrawable>> objects;
};

}

#endif
