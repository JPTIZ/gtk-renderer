#include "app.h"

#include <iostream>

#include "utils/signals.h"
#include "lib/render/geometry.h"

using namespace rudolph;
using namespace utils;

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
    using std::string;
    using std::bind;
    using namespace std::placeholders;

    auto builder = Gtk::Builder::create_from_file("res/ui/mainwindow.ui");

    auto drawing_area = utils::get_widget<Gtk::DrawingArea>(
        builder, "drawing-area"
    );

    link_all<Callback::Clicked, Gtk::Button>(
        _elms,
        builder,
        {
            signal(string{"btn-up"}, [this, drawing_area]() {
                std::cout << "Clicked 'up'\n";
                _renderer.window().offset({0, -10});
                drawing_area->queue_draw();
            }),
            signal(string{"btn-down"}, [this, drawing_area]() {
                std::cout << "Clicked 'down'\n";
                _renderer.window().offset({0, 10});
                drawing_area->queue_draw();
            }),
            signal(string{"btn-left"}, [this, drawing_area]() {
                std::cout << "Clicked 'left'\n";
                _renderer.window().offset({-10, 0});
                drawing_area->queue_draw();
            }),
            signal(string{"btn-right"}, [this, drawing_area]() {
                std::cout << "Clicked 'right'\n";
                _renderer.window().offset({10, 0});
                drawing_area->queue_draw();
            }),
        }
    );

    sig<Callback::Draw, Gtk::DrawingArea>(
        _elms,
        builder,
        "drawing-area",
        sigc::mem_fun(_renderer, &Renderer::on_draw)
    );

    _mainwindow = utils::get_widget<Gtk::ApplicationWindow>(
        builder, "main-window"
    );

    _mainwindow->set_application(_app);
    _app->add_window(*_mainwindow);

    _mainwindow->present();
}

}
}
