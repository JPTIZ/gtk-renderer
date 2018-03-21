#ifndef RUDOLPH_WINDOW_H
#define RUDOLPH_WINDOW_H

#include <memory>
#include <utility>

#include <gtk/gtk.h>

#include "render.h"
#include "geometry.h"

namespace rudolph {

class MainWindow {
    using Size = geometry::Size;
public:
    MainWindow(Size);

    void show();
    void close();
    void update_list();
    void configure_gui();

    Size size() const {
        return _size;
    }

    Renderer& get_renderer() {
        return renderer;
    }

private:
    Size _size{0, 0};
    GtkBuilder* gtk_builder;
    GtkWidget* gtk_window;
    Renderer renderer;
};

struct GtkInitError: std::runtime_error {
    using runtime_error::runtime_error;
};

}

#endif
