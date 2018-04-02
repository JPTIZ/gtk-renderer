#include "rudolph.h"

#include <gtk/gtk.h>

#include "window.h"

void rudolph::init(int& argc, char**& argv) {
    gtk_init(&argc, &argv);
}

void rudolph::main(int& argc, char**& argv) {
    init(argc, argv);

    auto window = MainWindow{geometry::Size{600, 600}};
    window.show();

    gtk_main();
}
