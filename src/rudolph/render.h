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
    using Rect = geometry::Rect;
public:
    RenderTarget(GtkWidget*);
    ~RenderTarget();

    Point2D world_to_viewport(int xw, int yw);
    Point2D world_to_viewport(Point2D p);
    void draw_point(Point2D);
    void draw_line(Point2D, Point2D);
    void resize(Size size);
    void move_camera(int dx, int dy);
    void invalidate(Rect);
    void set_target(GtkWidget*);

    cairo_surface_t* surface() const {
        return back_buffer_;
    }

    void zoom(double ratio) {
        zoom_ratio_ += ratio;
    }

    double zoom_ratio() const;

    GtkWidget* parent_() const {
        return parent;
    }

private:
    cairo_surface_t* back_buffer_ = nullptr;
    GtkWidget* parent;
    CameraWindow camera_window;
    Viewport viewport;

    double zoom_ratio_ = 1.0;
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

    cairo_surface_t* surface() const {
        return target.surface();
    }

    RenderTarget& render_target() {
        return target;
    }

private:
    GtkWidget* parent;
    RenderTarget target;
    std::vector<Drawable> _display_file;
};

}

#endif
