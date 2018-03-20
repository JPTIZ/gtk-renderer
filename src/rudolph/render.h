#ifndef RUDOLPH_RENDER_H
#define RUDOLPH_RENDER_H

#include <memory>
#include <vector>

#include <gtk/gtk.h>

#include "geometry.h"
#include "drawable.h"
#include "objects/camerawindow.h"
#include "objects/viewport.h"
#include "../utils.h"

namespace rudolph {

/**
 * Drawable canvas.
 *
 * Abstracts the idea of an output drawing target.
 */
class RenderTarget {
    using Point2D = geometry::Point;
    using Size = geometry::Size;
public:
    RenderTarget(GtkWidget* parent);

    Point2D camera_to_viewport(int xw, int yw);
    Point2D camera_to_viewport(Point2D p);
    void draw_point(Point2D);
    void draw_line(Point2D, Point2D);
    void resize(Size size);

    cairo_surface_t* surface() const {
        return surface_;
    }

    void surface(cairo_surface_t* surface) {
        surface_ = surface;
    }

private:
    double ratio() const;

    cairo_surface_t* surface_ = nullptr;
    GtkWidget* parent;
    CameraWindow camera_window;
    Viewport viewport;
};

/**
 * Manages drawable components and applies window/viewport transformations.
 */
class Renderer {
    using Size = geometry::Size;
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
    void resize(Size size);

    template <typename T>
    void add_object(T x) {
        _display_file.push_back( Drawable(std::move(x)) );
    }

    std::vector<Drawable> display_file() const {
        return _display_file;
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
    std::vector<Drawable> _display_file;
};

}

#endif
