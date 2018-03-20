#include "render.h"

#include "geometry.h"
#include "objects/shapes.h"

#include <utility>

namespace {
    using namespace rudolph;

    using Rect = geometry::Rect;

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
}
using Point2D = geometry::Point;

Renderer::Renderer(GtkWidget* parent):
    target{parent},
    parent{parent}
{
    g_signal_connect(parent, "draw", G_CALLBACK(on_draw), this);
    g_signal_connect(parent, "configure-event", G_CALLBACK(on_config_event), this);
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

RenderTarget::RenderTarget(GtkWidget *parent):
        parent{parent}
{
    GtkRequisition parent_size;
    gtk_widget_get_preferred_size(parent, NULL, &parent_size);

    camera_window->set_width((int)parent_size.width);
    camera_window->set_height((int)parent_size.height);

    viewport->set_width((int)parent_size.width);
    viewport->set_height((int)parent_size.height);
}

Point2D RenderTarget::camera_to_viewport(int xw, int yw) {
    int xv = (xw - camera_window->bottom_left().x) / (camera_window->top_right().x - camera_window->bottom_left().x);
    xv *= viewport->bottom_right().x - viewport->top_left().x;

    int yv = 1 - (yw - camera_window->bottom_left().y) / (camera_window->top_right().y - camera_window->bottom_left().y);
    yv *= viewport->bottom_right().y - viewport->top_left().y;

    return Point2D{xv, yv};
}

Point2D RenderTarget::camera_to_viewport(Point2D p) {
    int xv = (p.x - camera_window->bottom_left().x) / (camera_window->top_right().x - camera_window->bottom_left().x);
    xv *= viewport->bottom_right().x - viewport->top_left().x;

    int yv = 1 - (p.y - camera_window->bottom_left().y) / (camera_window->top_right().y - camera_window->bottom_left().y);
    yv *= viewport->bottom_right().y - viewport->top_left().y;

    return Point2D{xv, yv};
}

void RenderTarget::draw_point(Point2D p) {
    Point2D vpoint = camera_to_viewport(p);
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
    Point2D va = camera_to_viewport(a);
    Point2D vb = camera_to_viewport(b);

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
