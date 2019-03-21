#ifndef RUDOLPH_APP_H
#define RUDOLPH_APP_H

#include <gtkmm.h>
#include <memory>
#include "../lib/render/renderer.h"

namespace rudolph {
namespace app {

class Rudolph {
public:
    Rudolph();

    void run() {
        _app->run();
    }

private:
    DisplayFile _display_file = DisplayFile();
    Renderer _renderer = Renderer(_display_file);

    Glib::RefPtr<Gtk::Application> _app;
    std::shared_ptr<Gtk::ApplicationWindow> _mainwindow;
    std::shared_ptr<Gtk::DrawingArea> _drawing_area;

    void create_mainwindow();

};

}
}

#endif
