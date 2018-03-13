#ifndef RUDOLPH_RENDER_H
#define RUDOLPH_RENDER_H

#include <memory>
#include <vector>

#include <gtk/gtk.h>

#include "geometry.h"
#include "../utils.h"

namespace rudolph {

using Viewport = geometry::Rect;
using Window = geometry::Rect;

class RenderTarget;

/**
 * Drawable canvas.
 *
 * Abstracts the idea of an output drawing target.
 */
class RenderTarget {
    using Point = geometry::Point;
public:
    RenderTarget(GtkWidget* parent):
        parent{parent}
    {}

    void draw_point(Point);
    void draw_line(Point, Point);

    cairo_surface_t* surface() const {
        return surface_;
    }

    void surface(cairo_surface_t* surface) {
        surface_ = surface;
    }

private:
    cairo_surface_t* surface_ = nullptr;
    GtkWidget* parent;
};

class Drawable {
public:
    template <typename T>
    Drawable(T t):
        data{utils::make_unique<ModelImpl<T>>(std::move(t))}
    {}

    Drawable(const Drawable& other):
        data{other.data->copy()}
    {}

    Drawable(Drawable&& other):
        data{std::move(other.data)}
    {}

    void draw(RenderTarget& target) const {
        data->draw(target);
    }

private:
    /**
     * DrawableImpl components' interface
     */
    struct Model {
        virtual ~Model() = default;
        virtual std::unique_ptr<Model> copy() const = 0;
        virtual void draw(RenderTarget&) const = 0;
    };

    template <typename T>
    struct ModelImpl: Model {
        ModelImpl(T x):
            x{x}
        {}

        std::unique_ptr<Model> copy() const override {
            return utils::make_unique<ModelImpl>(*this);
        }

        void draw(RenderTarget& target) const override {
            x.draw(target);
        }

        T x;
    };

    std::unique_ptr<Model> data;
};

/**
 * Manages drawable components and applies window/viewport transformations.
 */
class Renderer {
    using DisplayList = std::vector<std::pair<std::string, Drawable>>;
public:
    /**
     * Creates a renderer for a given window.
     *
     * @param parent Parent GtkWindow.
     */
    Renderer(GtkWidget* parent);

    ~Renderer() {
        if (surface()) {
            cairo_surface_destroy(surface());
        }
    }

    void refresh();
    void clear();

    template <typename T>
    void add_object(std::string name, T x) {
        objects_.push_back(
            std::make_pair(
                std::move(name),
                Drawable(std::move(x))
            )
        );
    }

    DisplayList objects() const {
        return objects_;
    }

    void surface(cairo_surface_t* surface) {
        target.surface(surface);
    }

    cairo_surface_t* surface() const {
        return target.surface();
    }

private:
    GtkWidget* parent;
    RenderTarget target;
    DisplayList objects_;
};

}

#endif
