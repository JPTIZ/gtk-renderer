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
    using Point2D = geometry::Point2D;
    using Size = geometry::Size;
public:
    RenderTarget();
    ~RenderTarget();

    Point2D world_to_normal(double xw, double yw);
    Point2D world_to_normal(Point2D p);
    Point2D normal_to_viewport(double xw, double yw);
    Point2D normal_to_viewport(Point2D p);
    Point2D world_to_viewport(double xw, double yw);
    Point2D world_to_viewport(Point2D p);

    void clear();
    void draw_point(Point2D);
    void draw_line(Point2D, Point2D);
    void draw_polygon(std::vector<Point2D> points, bool filled);
    void draw_viewport();
    void move_camera(double dx, double dy);

    CameraWindow& window() {
        return camera_window;
    }

    const CameraWindow& window() const {
        return camera_window;
    }

    Viewport& get_viewport() {
        return viewport;
    }

    const Viewport& get_viewport() const {
        return viewport;
    }

    cairo_surface_t* surface() const {
        return back_buffer_;
    }

    void zoom(double ratio);

    double step() const {
        return _step;
    }

private:
    CameraWindow camera_window;
    Viewport viewport;
    cairo_surface_t* back_buffer_ = nullptr;
    double _step = 10;
};

/**
 * Manages drawable components and applies window/viewport transformations.
 */
class Renderer {
    using Size = geometry::Size;
    using Rect = geometry::Rect;
public:
    /**
     * Creates a renderer for a given window.
     *
     * @param parent Parent GtkWindow.
     */
    Renderer(GtkWidget*);

    void refresh();
    void clear();
    void invalidate();
    void invalidate(Rect);

    template <typename T>
    void add_object(T x) {
        _display_file.push_back(Drawable(std::move(x)));
    }

    std::vector<Drawable> display_file() const {
        return _display_file;
    }

    std::vector<Drawable>& display_file() {
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
