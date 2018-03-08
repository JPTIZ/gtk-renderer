#include "render.h"

#include <iostream>

static gboolean
draw_cb(GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data)
{
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  return FALSE;
}

namespace {
    using namespace rudolph;
}

void RenderTarget::draw_point(Point p) {
    auto x = p.x;
    auto y = p.y;

    auto cr = cairo_create(&surface);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);

    cairo_rectangle (cr, x - 3, y - 3, 6, 6);
    cairo_fill (cr);

    cairo_stroke(cr);

    cairo_destroy(cr);

    gtk_widget_queue_draw_area (parent, 0, 0, 600, 600);
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
    auto cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_paint(cr);

    cairo_destroy(cr);

    gtk_widget_queue_draw_area (parent, 0, 0, 600, 600);
}
