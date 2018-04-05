#include "render.h"

#include "geometry.h"
#include "objects/shapes.h"
#include "matrix.h"

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
        auto renderer = reinterpret_cast<RenderTarget*>(data);
        renderer->resize({event->width, event->height});

        return true;
    }


    gboolean on_resize(
            GtkWidget* widget,
            GtkAllocation* event,
            gpointer* data)
    {
        auto renderer = reinterpret_cast<Renderer*>(data);
        renderer->resize({event->width, event->height});
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
        //std::cout << "scrollou: " << delta << std::endl;
        auto target = reinterpret_cast<Renderer*>(data)->render_target();
        target.zoom(delta);
        return true;
    }

    Size parent_size(GtkWidget* parent) {
        GtkRequisition parent_size;
        gtk_widget_get_preferred_size(parent, nullptr, &parent_size);
        return Size{parent_size.width, parent_size.height};
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
    for (auto obj: _display_file)
    {
        obj.draw(target);
    }
}


void Renderer::clear()
{
    target.clear();
}


void Renderer::resize(Size size)
{
    target.resize(size);
}


RenderTarget::RenderTarget():
    camera_window{Size{800, 600}},
    viewport{Size{800, 600}},
    back_buffer_{
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                   viewport.width(),
                                   viewport.height())}
{}


RenderTarget::~RenderTarget() {
    cairo_surface_destroy(surface());
}


Point2D RenderTarget::world_to_viewport(double xw, double yw) {
    /*auto camera_d = camera_window.top_right() - camera_window.bottom_left();
    auto viewport_d = viewport.bottom_right() - viewport.top_left();

    auto pcam = Point2D{xw, yw} - camera_window.bottom_left();

    auto xv = pcam.x() * viewport_d.x() / camera_d.x();
    auto yv = viewport_d.y() - (viewport_d.y() / camera_d.y() * pcam.y());

    return Point2D{xv, yv} * zoom_ratio_;*/

    Matrix<double> coord(1, 3);
    coord(0, 0) = xw;
    coord(0, 1) = yw;
    coord(0, 2) = 1;

    double cos_vy = std::cos(camera_window.angle());
    double sin_vy = std::sin(camera_window.angle());

    // Normalized Coordinates
    // Translate to origin, rotate, and scale
    Matrix<double> normalizer(3, 3);
    normalizer(0, 0) = cos_vy * 2/camera_window.width();
    normalizer(0, 1) = -sin_vy * 2/camera_window.height();
    normalizer(1, 0) = sin_vy * 2/camera_window.width();
    normalizer(1, 1) = cos_vy * 2/camera_window.height();
    normalizer(2, 0) = (-cos_vy*camera_window.bottom_left().x() - sin_vy*camera_window.bottom_left().y())*2/camera_window.width();
    normalizer(2, 1) = (sin_vy*camera_window.bottom_left().x() - cos_vy*camera_window.bottom_left().y())*2/camera_window.height();
    normalizer(2, 2) = 1;

    coord = coord * normalizer;

    // Viewport Coordinates
    normalizer(0, 0) = viewport.width()/2;
    normalizer(0, 1) = 0;
    normalizer(1, 0) = 0;
    normalizer(1, 1) = -viewport.height()/2;
    normalizer(2, 0) = viewport.width()/2;
    normalizer(2, 1) = viewport.height()/2;

    coord = coord * normalizer;

    return Point2D{coord(0, 0), coord(0, 1)};
}


Point2D RenderTarget::world_to_viewport(Point2D p) {
    return world_to_viewport(p.x(), p.y());
}


void RenderTarget::clear() {
    ::clear(back_buffer_);
}


void RenderTarget::draw_point(Point2D p) {
    auto vpoint = world_to_viewport(p);
    auto x = vpoint.x();
    auto y = vpoint.y();

    auto region = Rect{x, y, 1, 1};

    auto cr = cairo_create(back_buffer_);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);

    cairo_rectangle(cr, region.x, region.y, region.width, region.height);
    cairo_fill(cr);

    cairo_destroy(cr);
}


void RenderTarget::draw_line(Point2D a, Point2D b) {
    auto va = world_to_viewport(a);
    auto vb = world_to_viewport(b);

    auto min_x = std::min(va.x(), vb.x());
    auto min_y = std::min(va.y(), vb.y());

    auto max_x = std::max(va.x(), vb.x());
    auto max_y = std::max(va.y(), vb.y());

    auto region = Rect{min_x, min_y, max_x - min_x, max_y - min_y};

    auto cr = cairo_create(back_buffer_);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);

    cairo_move_to(cr, va.x(), va.y());
    cairo_line_to(cr, vb.x(), vb.y());

    cairo_stroke(cr);
    cairo_destroy(cr);
}


void RenderTarget::resize(Size size) {
    viewport.resize(size.width, size.height);

    cairo_surface_destroy(back_buffer_);
    back_buffer_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                              viewport.width(),
                                              viewport.height());
}


void RenderTarget::move_camera(double dx, double dy) {
    camera_window.move(dx * _step, dy * _step);
}


double RenderTarget::zoom_ratio() const {
    return zoom_ratio_;
}

void Renderer::invalidate() {
    invalidate(Rect{0, 0,
                    gtk_widget_get_allocated_width(parent),
                    gtk_widget_get_allocated_height(parent)});
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
