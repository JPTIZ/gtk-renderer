#include "render.h"

#include "geometry.h"
#include "objects/shapes.h"
#include "matrix.h"
#include "clipper.h"

#include <utility>
#include <iostream>
#include <cmath>

namespace {
    using namespace rudolph;

    using Rect = geometry::Rect;
    using Size = geometry::Size;
    using Point2D = geometry::Point2D;


    void clear(cairo_surface_t* surface) {
        auto cr = cairo_create(surface);
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);
        cairo_destroy(cr);
    }


    cairo_surface_t* surface_from_widget(GtkWidget* widget) {
        auto surface = gdk_window_create_similar_surface(
                           gtk_widget_get_window(widget),
                           CAIRO_CONTENT_COLOR,
                           gtk_widget_get_allocated_width(widget),
                           gtk_widget_get_allocated_height(widget)
                       );
        clear(surface);
        return surface;
    }


    gboolean on_draw(GtkWidget* widget, cairo_t* cr, gpointer* data)
    {
        auto& renderer = *reinterpret_cast<Renderer*>(data);
        auto surface = renderer.surface();

        cairo_set_source_surface(cr, surface, 0, 0);
        clear(surface);

        renderer.refresh();
        renderer.invalidate();

        cairo_paint(cr);

        return false;
    }


    gboolean on_config_event(GtkWidget* widget,
                          GdkEventConfigure* event,
                          gpointer* data)
    {
        return true;
    }


    gboolean on_resize(
            GtkWidget* widget,
            GtkAllocation* event,
            gpointer* data)
    {
        return true;
    }


    gboolean on_key_press(
            GtkWidget* widget,
            GdkEventKey* event,
            gpointer* data)
    {
        auto renderer = reinterpret_cast<Renderer*>(data);
        auto& target = renderer->render_target();
        switch (event->keyval) {
            case GDK_KEY_Up:
                target.move_camera(0, -1);
                break;
            case GDK_KEY_Down:
                target.move_camera(0, 1);
                break;
            case GDK_KEY_Left:
                target.move_camera(1, 0);
                break;
            case GDK_KEY_Right:
                target.move_camera(-1, 0);
                break;
            case GDK_KEY_Page_Up:
                target.zoom(0.1);
                break;
            case GDK_KEY_Page_Down:
                target.zoom(-0.1);
                break;
        }
        return true;
    }


    gboolean on_scroll(
            GtkWidget* widget,
            GdkEventScroll* event,
            gpointer* data)
    {
        double delta = (event->direction * 2 - 1);
        delta /= 10;
        auto target = reinterpret_cast<Renderer*>(data)->render_target();
        target.zoom(delta);
        return true;
    }

    Size parent_size(GtkWidget* parent) {
        GtkRequisition parent_size;
        gtk_widget_get_preferred_size(parent, nullptr, &parent_size);
        return Size{(double)parent_size.width, (double)parent_size.height};
    }
}

Renderer::Renderer(GtkWidget* parent):
    parent{parent},
    target{}
{
    g_signal_connect(parent, "draw", G_CALLBACK(on_draw), this);
    g_signal_connect(parent, "configure-event", G_CALLBACK(on_config_event), &target);
    g_signal_connect(parent, "size-allocate", G_CALLBACK(on_resize), this);
    g_signal_connect(parent, "key-press-event", G_CALLBACK(on_key_press), this);

    gtk_widget_add_events(GTK_WIDGET(parent), GDK_SCROLL_MASK);
    g_signal_connect(parent, "scroll-event", G_CALLBACK(on_scroll), this);
}


void Renderer::refresh()
{
    target.draw_viewport();

    for (auto obj: _display_file)
    {
        obj.draw(target);
    }
}


void Renderer::clear()
{
    target.clear();
}

RenderTarget::RenderTarget():
    camera_window{Size{520, 520}},
    viewport{Size{520, 520}},
    back_buffer_{
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                   viewport.width()+20,
                                   viewport.height()+20) }
{}


RenderTarget::~RenderTarget() {
    cairo_surface_destroy(surface());
}

Point2D RenderTarget::world_to_normal(double xw, double yw) {
    Matrix<double> coord(1, 3);
    coord(0, 0) = xw;
    coord(0, 1) = yw;
    coord(0, 2) = 1;

    double cos_vy = std::cos(camera_window.angle());
    double sin_vy = std::sin(camera_window.angle());
    double cam_x = camera_window.bottom_left().x();
    double cam_y = camera_window.bottom_left().y();

    // Normalized Coordinates
    // Translate to origin, rotate, and scale
    auto vec = std::vector<double>{
        cos_vy * 2/camera_window.width(), -sin_vy * 2/camera_window.height(), 0,
        sin_vy * 2/camera_window.width(), cos_vy * 2/camera_window.height(), 0,
        (-cos_vy*cam_x - sin_vy*cam_y)*2/camera_window.width(),
        (sin_vy*cam_x - cos_vy*cam_y)*2/camera_window.height(),
        1 };
    Matrix<double> normalizer(vec);
    normalizer.width(3);
    normalizer.height(3);
    
    coord = coord * normalizer;

    return Point2D{coord(0, 0), coord(0, 1)};
}

Point2D RenderTarget::world_to_normal(Point2D p) {
    return world_to_normal(p.x(), p.y());
}

Point2D RenderTarget::normal_to_viewport(double xw, double yw) {
    Matrix<double> coord(1, 3);
    coord(0, 0) = xw;
    coord(0, 1) = yw;
    coord(0, 2) = 1;

    // Viewport Coordinates
    auto vec = std::vector<double>{
        (double)viewport.width()/2, 0, 0,
        0, (double)-viewport.height()/2, 0,
        viewport.top_left().x()+(double)viewport.width()/2, viewport.top_left().y()+(double)viewport.height()/2, 1
    };
    Matrix<double> viewporter(vec);
    viewporter.width(3);
    viewporter.height(3);
    
    coord = coord * viewporter;

    return Point2D{coord(0, 0), coord(0, 1)};
}

Point2D RenderTarget::normal_to_viewport(Point2D p) {
    return normal_to_viewport(p.x(), p.y());
}

Point2D RenderTarget::world_to_viewport(double xw, double yw) {
    auto normalized = world_to_normal(xw, yw);
    return normal_to_viewport(normalized.x(), normalized.y());
}

Point2D RenderTarget::world_to_viewport(Point2D p) {
    return world_to_viewport(p.x(), p.y());
}

void RenderTarget::clear() {
    ::clear(back_buffer_);
}

void RenderTarget::draw_point(Point2D p) {
    auto clipped = Clipper().clip_point(p);

    if (clipped) // if point was clipped it is out of the window
        return;  // no need to draw it

    auto vpoint = normal_to_viewport(p);
    auto x = vpoint.x();
    auto y = vpoint.y();

    auto region = Rect{x, y, 1, 1};

    auto cr = cairo_create(back_buffer_);

    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_set_line_width(cr, 1);

    cairo_rectangle(cr, region.x, region.y, region.width, region.height);
    cairo_fill(cr);

    cairo_destroy(cr);
}

void RenderTarget::draw_line(Point2D a, Point2D b) {
    auto clipper = Clipper(ClipMethod::LIANG_BARSKY);

    std::vector<Point2D> clipped = clipper.clip_line(a, b);

    if (clipped.size() > 0) {
        auto va = normal_to_viewport(clipped[0]);
        auto vb = normal_to_viewport(clipped[1]);

        auto cr = cairo_create(back_buffer_);

        cairo_set_source_rgb(cr, 0, 0, 1);
        cairo_set_line_width(cr, 1);

        cairo_move_to(cr, va.x(), va.y());
        cairo_line_to(cr, vb.x(), vb.y());

        cairo_stroke(cr);
        cairo_destroy(cr);
    }
}

void RenderTarget::draw_polygon(std::vector<Point2D> points, bool filled) {
    auto cr = cairo_create(back_buffer_);
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_set_line_width(cr, 1);

    auto clipper = Clipper();
    std::vector<Point2D> clipped = clipper.clip_polygon(points);

    if (clipped.size() > 0) {
        // Move to first point
        auto va = normal_to_viewport(clipped[0]);
        cairo_move_to(cr, va.x(), va.y());
        // Iterate through every point
        for (auto i = 1u; i < clipped.size(); ++i) {
            auto vb = normal_to_viewport(clipped[i]);

            cairo_line_to(cr, vb.x(), vb.y());
        }
        // Go back to first point to close polygon
        cairo_line_to(cr, va.x(), va.y());

        if (filled) {
            cairo_fill(cr);
        } else {
            cairo_stroke(cr);
        }

        cairo_destroy(cr);
    }
}

void RenderTarget::draw_viewport() {
    auto cr = cairo_create(back_buffer_);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);

    // Move to first point
    auto va = viewport.top_left();
    cairo_move_to(cr, va.x(), va.y());

    auto vb = va;
    vb.x() += viewport.width();
    cairo_line_to(cr, vb.x(), vb.y());

    vb.y() += viewport.height();
    cairo_line_to(cr, vb.x(), vb.y());

    vb.x() -= viewport.width();
    cairo_line_to(cr, vb.x(), vb.y());

    cairo_line_to(cr, va.x(), va.y());

    cairo_stroke(cr);
    cairo_destroy(cr);
}

void RenderTarget::move_camera(double dx, double dy) {
    camera_window.move(dx * _step, dy * _step);
}

void RenderTarget::zoom(double ratio) {
    camera_window.zoom(ratio);
}

void Renderer::invalidate() {
    invalidate(Rect{0, 0,
                    (double)gtk_widget_get_allocated_width(parent),
                    (double)gtk_widget_get_allocated_height(parent)});
}

void Renderer::invalidate(Rect region) {
    gtk_widget_queue_draw_area(
            parent,
            region.x - 1,
            region.y - 1,
            region.width + 2,
            region.height + 2
    );
}
