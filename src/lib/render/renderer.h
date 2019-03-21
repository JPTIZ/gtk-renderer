#ifndef RENDERER_H
#define RENDERER_H

#include <gtkmm.h>

class Renderer {
public:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:
};

#endif