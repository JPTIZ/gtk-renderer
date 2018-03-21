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
    camera_window{Size{512, 560}},
    viewport{Size{512, 560}}
{}

Point2D RenderTarget::world_to_viewport(int xw, int yw) {
    auto camera_d = Point2D{camera_window.top_right().x - camera_window.bottom_left().x, camera_window.top_right().y - camera_window.bottom_left().y};
    auto viewport_d = Point2D{viewport.bottom_right().x - viewport.top_left().x, viewport.bottom_right().y - viewport.top_left().y};

    auto pw = Point2D{xw, yw};

    auto xv = pw.x * viewport_d.x / camera_d.x;
    auto yv = viewport_d.y - (viewport_d.y / camera_d.y * pw.y);

    return Point2D{xv, yv};
}

Point2D RenderTarget::world_to_viewport(Point2D p) {
    return world_to_viewport(p.x, p.y);
}

void RenderTarget::draw_point(Point2D p) {
    auto vpoint = world_to_viewport(p);
    auto x = vpoint.x;
    auto y = vpoint.y;

    auto thickness = ratio();
    auto region = Rect{x, y, (int)thickness, (int)thickness};

    auto cr = cairo_create(surface());

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, thickness);

    cairo_rectangle(cr, region.x, region.y, region.width, region.height);
    cairo_fill(cr);

    cairo_destroy(cr);

    gtk_widget_queue_draw_area(parent, region.x, region.y, region.width, region.height);
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

    auto thickness = 0.5 * ratio();
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, thickness);

    cairo_move_to(cr, va.x, va.y + thickness);
    cairo_line_to(cr, vb.x, vb.y + thickness);

    cairo_stroke(cr);
    cairo_destroy(cr);

    gtk_widget_queue_draw_area(
            parent,
            region.x,
            region.y,
            region.width,
            region.height
    );
}

void RenderTarget::resize(Size size) {
    camera_window.set_width(size.width);
    camera_window.set_height(size.height);
    viewport.set_width(size.width);
    viewport.set_height(size.height);
}

double RenderTarget::ratio() const {
    // This function is actually pretty stupid and serves only for lines to look thicker.
    auto wv = viewport.width();
    auto hv = viewport.height();

    auto ww = camera_window.width();
    auto hw = camera_window.height();

    auto thickness = (wv / ww + hv / hw) / 2;
    return (thickness>0.5)?thickness:1;
}