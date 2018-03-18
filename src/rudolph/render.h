#ifndef RUDOLPH_RENDER_H
#define RUDOLPH_RENDER_H

#include <memory>
#include <vector>

#include <gtk/gtk.h>

#include "geometry.h"
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
public:
    RenderTarget(GtkWidget* parent);

    Point2D camera_to_viewport(int xw, int yw);
    void draw_point(Point2D);
    void draw_line(Point2D, Point2D);

    cairo_surface_t* surface() const {
        return surface_;
    }

    void surface(cairo_surface_t* surface) {
        surface_ = surface;
    }

private:
    cairo_surface_t* surface_ = nullptr;
    GtkWidget* parent;
    CameraWindow* camera_window;
    Viewport* viewport;
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
