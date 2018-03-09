#include "render.h"

#include <geometry.h>

#include <utility>


namespace {
    using namespace rudolph;

    using Rect = geometry::Rect;
}

gboolean rudolph::draw_event(GtkWidget* widget, cairo_t* cr, gpointer* data)
{
    auto renderer = reinterpret_cast<Renderer*>(data);
    auto surface = renderer->surface();

    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    renderer->refresh();

    return FALSE;
}

gboolean rudolph::config_event(GtkWidget* widget,
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

void RenderTarget::draw_point(Point p) {
    auto x = p.x;
    auto y = p.y;

    auto region = Rect{x, y, 1, 1};

    auto cr = cairo_create(surface());

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);

    cairo_rectangle(cr, region.x, region.y, region.width, region.height);
    cairo_fill(cr);

    cairo_stroke(cr);
    cairo_destroy(cr);

    gtk_widget_queue_draw_area(parent, region.x, region.y, region.width, region.height);
}

void RenderTarget::draw_line(Point a, Point b) {
    auto min_x = std::min(a.x, b.x);
    auto min_y = std::min(a.y, b.y);

    auto max_x = std::max(a.x, b.x);
    auto max_y = std::max(a.y, b.y);

    auto region = Rect{min_x, min_y, max_x - min_x, max_y - min_y};

    auto cr = cairo_create(surface());

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);

    cairo_move_to(cr, a.x, a.y);
    cairo_line_to(cr, b.x, b.y);

    cairo_close_path(cr);

    cairo_stroke(cr);
    cairo_destroy(cr);

    gtk_widget_queue_draw_area(
            parent,
            region.x,
            region.y,
            region.width + 4,
            region.height + 4
    );
}

void Renderer::refresh() {
    for (auto obj: objects_) {
        obj.second.draw(target);
    }
}

void Renderer::clear() {
    // TODO
}
