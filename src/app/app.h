#ifndef RUDOLPH_APP_H
#define RUDOLPH_APP_H

#include <gtkmm.h>
#include <memory>

namespace rudolph {
namespace app {

class Rudolph {
public:
    Rudolph();

    void run() {
        _app->run();
    }

private:
    void create_mainwindow();

    Glib::RefPtr<Gtk::Application> _app;
    std::shared_ptr<Gtk::ApplicationWindow> _mainwindow;
    std::shared_ptr<Gtk::DrawingArea> _drawing_area;
};

}
}

#endif
