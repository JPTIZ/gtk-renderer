#ifndef RUDOLPH_RENDER_H
#define RUDOLPH_RENDER_H

#include <memory>
#include <vector>

#include <gtk/gtk.h>

#include "geometry.h"
#include "../utils.h"

namespace rudolph {

/**
 * Drawable canvas.
 *
 * Abstracts the idea of an output drawing target.
 */
class RenderTarget {
    using Point = geometry::Point;
public:
    RenderTarget(cairo_surface_t& surface, GtkWidget* parent):
        surface{surface},
        parent{parent}
    {}

    void draw_point(Point);
    void draw_line(Point, Point);

private:
    cairo_surface_t& surface;
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
public:
    /**
     * Creates a renderer for a given window.
     *
     * @param parent Parent GtkWindow.
     */
    Renderer(GtkWidget* parent):
        surface{
            gdk_window_create_similar_surface(
                gtk_widget_get_window(parent),
                CAIRO_CONTENT_COLOR,
                gtk_widget_get_allocated_width(parent),
                gtk_widget_get_allocated_height(parent)
            )
        },
        target{*surface, parent},
        parent{parent}
    {
    }

    ~Renderer() {
        if (surface) {
            cairo_surface_destroy(surface);
        }
    }

    void refresh();
    void clear();

    template <typename T>
    void add_object(T x) {
        objects.push_back(Drawable(std::move(x)));
    }

private:
    cairo_surface_t* surface;
    GtkWidget* parent;
    RenderTarget target;
    std::vector<Drawable> objects;
};

}

#endif
