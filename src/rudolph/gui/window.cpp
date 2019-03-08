#include "window.h"

namespace {

template <typename T>
using RefPtr = Glib::RefPtr<T>;

}

namespace rudolph {
namespace gui {

using Size = geometry::Size;

MainWindow::MainWindow(Size size, Glib::RefPtr<Gtk::Application>& app):
    Gtk::ApplicationWindow{app},
    _size{size}
{}

void MainWindow::show() {
    Gtk::ApplicationWindow::show_all();
}

}
}
