#include "render.h"

#include "geometry.h"
#include "objects/shapes.h"

#include <utility>

namespace {
    using namespace rudolph;

    using Rect = geometry::Rect;
    using Size = geometry::Size;
    using Point2D = geometry::Point;

    gboolean on_draw(GtkWidget* widget, cairo_t* cr, gpointer* data)
    {
        auto renderer = reinterpret_cast<Renderer*>(data);
        auto surface = renderer->surface();

        cairo_set_source_surface(cr, surface, 0, 0);
        cairo_paint(cr);

        renderer->refresh();

        return false;
    }

    gboolean on_config_event(GtkWidget* widget,
                          GdkEventConfigure* event,
                          gpointer* data)
    {
        auto target = reinterpret_cast<Renderer*>(data);

        auto surface = gdk_window_create_similar_surface(
                           gtk_widget_get_window(widget),
                           CAIRO_CONTENT_COLOR,
                           gtk_widget_get_allocated_width(widget),
                           gtk_widget_get_allocated_height(widget)
                       );

        auto cr = cairo_create(surface);
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);
        cairo_destroy(cr);

        target->surface(surface);

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
    camera_window{parent_size(parent)},
    viewport{parent_size(parent)}
{}

Point2D RenderTarget::camera_to_viewport(int xw, int yw) {
    auto camera_d = camera_window.bottom_left() - camera_window.top_right();
    auto viewport_d = viewport.bottom_right() - viewport.top_left();

    auto xv = viewport_d.x * (xw - camera_window.bottom_left().x) / -camera_d.x;

    auto yv = viewport_d.y * (1 - (yw - camera_window.bottom_left().y) / -camera_d.y);

    return Point2D{xv, yv};
}

Point2D RenderTarget::camera_to_viewport(Point2D p) {
    return camera_to_viewport(p.x, p.y);
}

void RenderTarget::draw_point(Point2D p) {
    auto vpoint = camera_to_viewport(p);
    auto x = vpoint.x;
    auto y = vpoint.y;

    auto region = Rect{x, y, 1, 1};

    auto cr = cairo_create(surface());

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);

    cairo_rectangle(cr, region.x, region.y, region.width, region.height);
    cairo_fill(cr);

    cairo_destroy(cr);

    gtk_widget_queue_draw_area(parent, region.x, region.y, region.width, region.height);
}

void RenderTarget::draw_line(Point2D a, Point2D b) {
    auto va = camera_to_viewport(a);
    auto vb = camera_to_viewport(b);

    auto min_x = std::min(va.x, vb.x);
    auto min_y = std::min(va.y, vb.y);

    auto max_x = std::max(va.x, vb.x);
    auto max_y = std::max(va.y, vb.y);

    auto region = Rect{min_x, min_y, max_x - min_x, max_y - min_y};

    auto cr = cairo_create(surface());

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, .5);

    cairo_move_to(cr, va.x, va.y + .5);
    cairo_line_to(cr, vb.x, vb.y + .5);

    cairo_stroke(cr);
    cairo_destroy(cr);

    gtk_widget_queue_draw_area(
            parent,
            region.x - 1,
            region.y - 1,
            region.width + 1,
            region.height + 1
    );
}

void RenderTarget::resize(Size size) {
    camera_window.set_width(size.width);
    camera_window.set_height(size.height);
    viewport.set_width(size.width);
    viewport.set_height(size.height);
}
