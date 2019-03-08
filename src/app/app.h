#ifndef RUDOLPH_APP_H
#define RUDOLPH_APP_H

#include <gtkmm.h>
#include <memory>

#include "rudolph/gui/window.h"

namespace rudolph {
namespace app {

class Rudolph {
public:
    Rudolph();

private:
    Glib::RefPtr<Gtk::Application> _app;
    std::unique_ptr<rudolph::gui::MainWindow> _window;
};

}
}

#endif
