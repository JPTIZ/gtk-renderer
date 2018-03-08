#include "render.h"

#include <iostream>

/*
static gboolean draw_cb(GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data) {
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    return false;
}
*/

namespace {
    using namespace rudolph;
}

/*
gboolean rudolph::draw_event(GtkWidget* widget)
{
}
*/

gboolean rudolph::config_event(GtkWidget* widget,
                      GdkEventConfigure* event,
                      gpointer* data)
{
    std::cout << "config-event\n";
    auto target = reinterpret_cast<RenderTarget*>(data);

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

    target->surface = surface;

    return true;
}

void RenderTarget::draw_point(Point p) {
    auto x = p.x;
    auto y = p.y;

    auto cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);

    cairo_rectangle (cr, x - 3, y - 3, 60, 60);
    cairo_fill (cr);

    cairo_stroke(cr);

    cairo_destroy(cr);

    gtk_widget_queue_draw_area(parent, 0, 0, 600, 600);
}

void RenderTarget::draw_line(Point a, Point b) {
}

void Renderer::refresh() {
    std::cout << "refreshing\n";

    for (auto obj: objects) {
        obj.draw(target);
    }
}

void Renderer::clear() {
    std::cout << "clearing\n";
    /*
    auto cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_paint(cr);

    cairo_destroy(cr);

    gtk_widget_queue_draw_area(parent, 0, 0, 600, 600);
    */
}
