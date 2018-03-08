#include "rudolph.h"

#include <iostream>

#include <gtk/gtk.h>

#include "window.h"

void rudolph::init(int& argc, char**& argv) {
    gtk_init(&argc, &argv);
}

void rudolph::main(int& argc, char**& argv) {
    init(argc, argv);

    auto gtk_builder = gtk_builder_new();
    if (not gtk_builder_add_from_file(gtk_builder, "mainwindow.ui", NULL)) {
        std::cout << "failed to initialize main window from UI file\n";
        return;
    }

    auto window = MainWindow{rudolph::geometry::Size{800, 600}, gtk_builder};
    window.show();

    gtk_main();
}
