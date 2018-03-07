#ifndef RUDOLPH_RUDOLPH_WINDOW_H
#define RUDOLPH_RUDOLPH_WINDOW_H

#include <memory>
#include <utility>

#include <gtk/gtk.h>

#include "geometry.h"

namespace rudolph {

class MainWindow {
    using Size = geometry::Size;
public:
    MainWindow(Size);

    void show();
    void close();

    auto size() const {
        return _size;
    }

private:
    Size _size{0, 0};
    GtkWidget* gtk_window;
};

}

#endif
