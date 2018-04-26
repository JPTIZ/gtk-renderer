#include "dialog.h"

#include <iostream>
#include <utility>

namespace rudolph {

using Size = geometry::Size;

GtkWidget* create_gtk_dialog(GtkBuilder* gtk_builder, Size size, std::string filename) {
    auto err = (GError*)nullptr;
    if (not gtk_builder_add_from_file(gtk_builder, filename.c_str(), &err)) {
        throw std::runtime_error(
                std::string{"failed to initialize dialog window from UI file: "} +
                err->message + "\n");
    }

    auto gtk_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, "window"));
    gtk_window_set_default_size(GTK_WINDOW(gtk_window), size.width, size.height);

    return gtk_window;
}

DialogWindow::DialogWindow(Size size, std::string filename):
    _size{size},
    gtk_builder{gtk_builder_new()},
    gtk_window(create_gtk_dialog(gtk_builder, _size, filename))
{}

void DialogWindow::setup(std::vector<Event<void(GtkWidget*, void**)>>&& button_events) {
    for (auto event: button_events) {
        link_signal(event);
    }
}

void DialogWindow::show() {
    gtk_widget_show_all(gtk_window);
}

void DialogWindow::close() {
    gtk_widget_destroy(gtk_window);
}

}
