#include "app.h"

#include "utils/cppnew.h"
#include "utils/gtk.h"

using namespace rudolph;

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

    _drawing_area->signal_draw().connect(sigc::mem_fun(renderer, &Renderer::on_draw));

    _mainwindow->set_application(_app);
    _app->add_window(*_mainwindow);

    _mainwindow->present();
}


}
}
