#include "renderer.h"

bool Renderer::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // Prepare drawing area
    cr->set_line_width(2.0);
    cr->paint();
    cr->set_source_rgb(0.8, 0.0, 0.0);

    // Iterate the display file, drawing each object according to its type
    cr->move_to(0, 0);
    cr->line_to(50, 50);
    cr->stroke();

    return true;
}
