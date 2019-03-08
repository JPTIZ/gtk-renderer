#include "app.h"

#include "utils/cppnew.h"

using namespace rudolph;

using gui::MainWindow;

namespace rudolph {
namespace app {

Rudolph::Rudolph():
    _window{nullptr}
{
    _app = Gtk::Application::create("org.rudolph");
    _app->signal_activate().connect([this]() {
        _window = utils::make_unique<MainWindow>(
            geometry::Size{800, 600},
            _app
        );

        _app->add_window(*_window);

        _window->present();
    });
    _app->run();
}

}
}
