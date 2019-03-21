#include "app.h"

#include "utils/cppnew.h"
#include "utils/gtk.h"
#include <iostream>

using namespace rudolph;


bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
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

namespace rudolph {
namespace app {

Rudolph::Rudolph():
    _app{Gtk::Application::create("org.rudolph")},
    _mainwindow{nullptr}
{
    _app->signal_activate().connect(
        sigc::mem_fun(*this, &Rudolph::create_mainwindow)
    );
}

void Rudolph::create_mainwindow() {
    auto builder = Gtk::Builder::create_from_file("res/ui/mainwindow.ui");

    _mainwindow = utils::get_widget<Gtk::ApplicationWindow>(
            builder, "main_window"
    );

    _drawing_area = utils::get_widget<Gtk::DrawingArea>(
        builder, "drawing-area"
    );

    _drawing_area->signal_draw().connect(sigc::ptr_fun(&on_draw));

    _mainwindow->set_application(_app);
    _app->add_window(*_mainwindow);

    _mainwindow->present();
}


}
}
