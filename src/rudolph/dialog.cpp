#include "dialog.h"

#include <iostream>
#include <utility>

namespace rudolph {

using Size = geometry::Size;

void on_dial_close(GtkWidget* btn, gpointer* data) {
    reinterpret_cast<DialogWindow*>(data)->close();
}

GtkWidget* create_gtk_dialog(GtkBuilder* gtk_builder, Size size, std::string filename) {
    auto err = (GError*)nullptr;
    if (not gtk_builder_add_from_file(gtk_builder, filename.c_str(), &err)) {
        /*throw std::runtime_error(
                std::string{"failed to initialize dialog window from UI file: "} +
                err->message + "\n");*/
    }

    auto gtk_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, "window_new_obj"));
    gtk_window_set_default_size(GTK_WINDOW(gtk_window), size.width, size.height);
    gtk_window_set_title(GTK_WINDOW(gtk_window), "New Object");

    return gtk_window;
}

void on_btn_cancel(GtkWidget *widget, gpointer* data) {
    std::cout << "btn cancel" << std::endl;
}

void on_btn_ok(GtkWidget *widget, gpointer* data) {
    std::cout << "btn down" << std::endl;
    //auto& r = reinterpret_cast<DialogWindow*>(data)->get_renderer();
}

DialogWindow::DialogWindow(Size size, std::string filename):
    _size{size},
    gtk_builder{gtk_builder_new()},
    gtk_window(create_gtk_dialog(gtk_builder, _size, filename))
{
    g_signal_connect(gtk_window, "destroy", G_CALLBACK(on_dial_close), this);

    configure_gui();
}

void DialogWindow::configure_gui()
{
    // Signals for each and every button
    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_cancel"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_cancel), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_ok"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_ok), this);
}

void DialogWindow::show() {
    gtk_widget_show_all(gtk_window);
}

void DialogWindow::update_entries() {
    // to do
}

void DialogWindow::close() {
    gtk_main_quit();
}

}
