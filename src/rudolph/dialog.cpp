#include "dialog.h"

#include <iostream>
#include <utility>

namespace rudolph {

using Size = geometry::Size;

template <typename Signature>
void link_signal(GtkBuilder* gtk_builder, const Event<Signature>& event) {
    g_signal_connect(
            GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder),
                                              event.element_id.c_str())),
            event.event.c_str(),
            G_CALLBACK(event.callback()),
            event.parameters);
}

GtkWidget* create_gtk_dialog(GtkBuilder* gtk_builder, Size size, std::string filename) {
    auto err = (GError*)nullptr;
    if (not gtk_builder_add_from_file(gtk_builder, filename.c_str(), &err)) {
        throw std::runtime_error(
                std::string{"failed to initialize dialog window from UI file: "} +
                err->message + "\n");
    }

    auto gtk_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, "window"));
    //gtk_window_set_default_size(GTK_WINDOW(gtk_window), size.width, size.height);
    g_signal_connect(gtk_window, "destroy",
	                 G_CALLBACK(gtk_widget_destroyed),
	                 &gtk_window);

    return gtk_window;
}

DialogWindow::DialogWindow(Size size, std::string filename):
    _size{size},
    gtk_builder{gtk_builder_new()},
    gtk_window(create_gtk_dialog(gtk_builder, _size, filename))
{}

void DialogWindow::setup() {
    auto button_events = std::vector<Event<void(GtkWidget*, void**)>>{
        {"btn_cancel", "clicked",
            [](GtkWidget* w, gpointer* data) {
                std::cout << "btn cancel" << std::endl;
                reinterpret_cast<DialogWindow*>(data)->close();
            }, this},
        {"btn_ok", "clicked",
            [](GtkWidget* w, gpointer* data) {
                std::cout << "btn ok" << std::endl;
                reinterpret_cast<DialogWindow*>(data)->close();
            }, this},
        };

    for (auto event: button_events) {
        link_signal(gtk_builder, event);
    }
}

void DialogWindow::show() {
    gtk_dialog_run(GTK_DIALOG(gtk_window));
}

void DialogWindow::close() {
    std::cout << gtk_window << std::endl;
    gtk_widget_destroy(GTK_WIDGET(gtk_window));
}

}
