#ifndef RUDOLPH_WINDOW_H
#define RUDOLPH_WINDOW_H

#include <memory>
#include <utility>

#include <gtkmm.h>

#include "../utils/geometry.h"

namespace rudolph {

class MainWindow: public Gtk::ApplicationWindow {
    using Size = geometry::Size;
public:
    MainWindow(Size, Glib::RefPtr<Gtk::Application>&);

    void show();

    Size size() const {
        return _size;
    }

private:
    Size _size{0, 0};
    Gtk::ApplicationWindow gtk_window;
};

}

#endif
