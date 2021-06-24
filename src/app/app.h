#ifndef RUDOLPH_APP_H
#define RUDOLPH_APP_H

#include <gtkmm.h>
#include <map>
#include <memory>

#include "utils/gtk.h"
#include "../lib/render/renderer.h"

namespace rudolph {

namespace app {

class Rudolph {
public:
    using ElementMap = std::map<std::string, std::shared_ptr<Gtk::Widget>>;

    Rudolph();

    void run() {
        _app->run();
    }

private:
    DisplayFile _display_file = DisplayFile{};
    Renderer _renderer = Renderer{_display_file};

    Glib::RefPtr<Gtk::Application> _app;
    std::shared_ptr<Gtk::ApplicationWindow> _mainwindow;
    ElementMap _elms;

    void create_mainwindow();
};

}
}

#endif
