#include "renderer.h"
#include <iostream>

namespace rudolph {

bool Renderer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    // Prepare drawing area
    cr->set_line_width(2.0);
    cr->paint();
    cr->set_source_rgb(0.8, 0.0, 0.0);

    // Iterate the display file, drawing each object according to its type
    int n_objects = this->_display_file.size();
    std::cout << "Number of objects to draw: " << n_objects << std::endl;

    for(int i = 0; i < n_objects; i++) {
        std::shared_ptr<GraphicObject> object = this->_display_file.at(i);
        if (object != nullptr) {
            std::cout << "Drawing object #" << i << std::endl;
            object->draw(cr);
        }
    }
    cr->stroke();

    return true;
}

}