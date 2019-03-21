#ifndef RENDERER_H
#define RENDERER_H

#include <gtkmm.h>
#include "display_file.h"

namespace rudolph {

class Renderer {
public:
    Renderer(DisplayFile &display_file):
    _display_file{display_file}
    {};

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:
    DisplayFile &_display_file;
};

}

#endif