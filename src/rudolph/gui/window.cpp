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
{
    auto builder = Gtk::Builder::create_from_file("res/ui/mainwindow.ui");


}

void MainWindow::show() {
    Gtk::ApplicationWindow::show_all();
}

}
}
