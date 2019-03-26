#include "app.h"

#include "utils/cppnew.h"
#include "utils/gtk.h"
#include "lib/render/geometry.h"

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

    _display_file.add(std::make_shared<geometry::Line>(
        geometry::Vec2{60, 70},
        geometry::Vec2{80, 70}
    ));

    _display_file.add(std::make_shared<geometry::Point>(
        geometry::Vec2{100, 100}
    ));

    _display_file.add(std::make_shared<geometry::Polygon>(
        std::vector<geometry::Vec2>({
            geometry::Vec2{150, 150},
            geometry::Vec2{150, 200},
            geometry::Vec2{200, 200}
        })
    ));

    _display_file.add(std::make_shared<geometry::Polygon>(
        std::vector<geometry::Vec2>({
            geometry::Vec2{350, 350},
            geometry::Vec2{350, 400},
            geometry::Vec2{400, 400}
        })
    ));
}

void Rudolph::create_mainwindow() {
    auto builder = Gtk::Builder::create_from_file("res/ui/mainwindow.ui");

    _mainwindow = utils::get_widget<Gtk::ApplicationWindow>(
            builder, "main_window"
    );

    _drawing_area = utils::get_widget<Gtk::DrawingArea>(
        builder, "drawing-area"
    );

    _list_store = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(
        builder->get_object("object-list-store")
    );

    // auto row = *(_list_store->append());

    _drawing_area->signal_draw().connect(sigc::mem_fun(_renderer, &Renderer::on_draw));

    _mainwindow->set_application(_app);
    _app->add_window(*_mainwindow);

    _mainwindow->present();
}


}
}
