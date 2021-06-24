#ifndef RENDERER_H
#define RENDERER_H

#include <gtkmm.h>
#include "display_file.h"
#include "../algebra/matrix.h"
#include "window.h"

namespace rudolph {

class Renderer {
    using Window = render::Window;
    template <typename T>
    using Matrix = algebra::Matrix<T>;
public:
    Renderer(DisplayFile& display_file):
        _window{geometry::Vec2{0, 0}, geometry::Size{800, 600}},
        _display_file{display_file}
    {}

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

    const Window& window() const {
        return _window;
    }

    Window& window() {
        return _window;
    }

private:
    Matrix<int> _transform_matrix{3, 3};
    Window _window;
    DisplayFile &_display_file;
};

}

#endif
