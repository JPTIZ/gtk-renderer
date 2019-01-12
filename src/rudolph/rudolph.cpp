#include "rudolph.h"

#include "gui/window.h"

void rudolph::main() {
    auto app = Gtk::Application::create("rudolph");
    auto window = MainWindow{geometry::Size{800, 600}, app};

    window.show();
    app->run(window);
}
