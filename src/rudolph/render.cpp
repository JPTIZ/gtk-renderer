#include "render.h"

#include "geometry.h"
#include "objects/shapes.h"

#include <utility>
#include <iostream>

namespace {
    using namespace rudolph;

    using Rect = geometry::Rect;
    using Size = geometry::Size;
    using Point2D = geometry::Point;

    void clear(cairo_surface_t* surface) {
        auto cr = cairo_create(surface);
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);
        cairo_destroy(cr);
    }

    gboolean on_draw(GtkWidget* widget, cairo_t* cr, gpointer* data)
    {
        auto renderer = reinterpret_cast<Renderer*>(data);
        auto surface = renderer->surface();

        cairo_set_source_surface(cr, surface, 0, 0);
        clear(surface);

        renderer->refresh();
        cairo_paint(cr);

        return false;
    }

    gboolean on_config_event(GtkWidget* widget,
                          GdkEventConfigure* event,
                          gpointer* data)
    {
        auto renderer = reinterpret_cast<Renderer*>(data);

        auto surface = gdk_window_create_similar_surface(
                           gtk_widget_get_window(widget),
                           CAIRO_CONTENT_COLOR,
                           gtk_widget_get_allocated_width(widget),
                           gtk_widget_get_allocated_height(widget)
                       );

        clear(surface);

        renderer->surface(surface);
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

    Size parent_size(GtkWidget* parent) {
        GtkRequisition parent_size;
        gtk_widget_get_preferred_size(parent, nullptr, &parent_size);
        return Size{parent_size.width, parent_size.height};
    }
}

Renderer::Renderer(GtkWidget* parent):
    target{parent},
    parent{parent}
{
    g_signal_connect(parent, "draw", G_CALLBACK(on_draw), this);
    g_signal_connect(parent, "configure-event", G_CALLBACK(on_config_event), this);
    g_signal_connect(parent, "size-allocate", G_CALLBACK(on_resize), this);
}

void Renderer::refresh()
{
    for (auto obj : _display_file)
    {
        obj.draw(target);
    }
}

void Renderer::clear()
{
    // TODO
}

void Renderer::resize(Size size)
{
    target.resize(size);
}

RenderTarget::RenderTarget(GtkWidget *parent):
    parent{parent},
    camera_window{Size{800, 600}},
    viewport{Size{800, 600}}
{}

Point2D RenderTarget::world_to_viewport(int xw, int yw) {
    auto window = camera_window;
    auto camera_d = window.top_right() - window.bottom_left();
    auto viewport_d = viewport.bottom_right() - viewport.top_left();

    auto pcam = Point2D{xw, yw} - window.bottom_left();

    auto xv = pcam.x * viewport_d.x / camera_d.x;
    auto yv = viewport_d.y - (viewport_d.y / camera_d.y * pcam.y);

    return Point2D{xv, yv - 100} * zoom_ratio_;
}

Point2D RenderTarget::world_to_viewport(Point2D p) {
    return world_to_viewport(p.x, p.y);
}

void RenderTarget::draw_point(Point2D p) {
    auto vpoint = world_to_viewport(p);
    auto x = vpoint.x;
    auto y = vpoint.y;

    auto region = Rect{x, y, (int)zoom_ratio_, (int)zoom_ratio_};

    auto cr = cairo_create(surface());

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, zoom_ratio_);

    cairo_rectangle(cr, region.x, region.y, region.width, region.height);
    cairo_fill(cr);

    cairo_destroy(cr);

    invalidate(region);
}

void RenderTarget::draw_line(Point2D a, Point2D b) {
    auto va = world_to_viewport(a);
    auto vb = world_to_viewport(b);

    auto min_x = std::min(va.x, vb.x);
    auto min_y = std::min(va.y, vb.y);

    auto max_x = std::max(va.x, vb.x);
    auto max_y = std::max(va.y, vb.y);

    auto region = Rect{min_x, min_y, max_x - min_x, max_y - min_y};

    auto cr = cairo_create(surface());

    auto thickness = zoom_ratio();
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, thickness);

    cairo_move_to(cr, va.x, va.y + thickness);
    cairo_line_to(cr, vb.x, vb.y + thickness);

    cairo_stroke(cr);
    cairo_destroy(cr);

    invalidate(region);
}

void RenderTarget::resize(Size size) {
    viewport.set_width(size.width);
    viewport.set_height(size.height);
    camera_window.set_width(size.width);
    camera_window.set_height(size.height);
}

void RenderTarget::move_camera(int dx, int dy) {
    camera_window.move(dx, dy);
}

double RenderTarget::zoom_ratio() const {
    return zoom_ratio_;
}

void RenderTarget::invalidate(Rect region) {
    gtk_widget_queue_draw_area(
            parent,
            region.x - 2 * zoom_ratio_,
            region.y - 2 * zoom_ratio_,
            region.width + 4 * zoom_ratio_,
            region.height + 4 * zoom_ratio_
    );
}
