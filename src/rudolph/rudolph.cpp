#include "rudolph.h"

#include "gui/window.h"

void rudolph::main(int& argc, char**& argv) {
    auto window = MainWindow{geometry::Size{800, 700}};
    window.show();

    gtk_main();
}
