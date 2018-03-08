#include "window.h"

#include <iostream>
#include <utility>

namespace {

using namespace rudolph;
using namespace rudolph::geometry;

void in_close(GtkWidget* btn, gpointer* data) {
    reinterpret_cast<MainWindow*>(data)->close();
}

}

MainWindow::MainWindow(Size size, GtkBuilder* gtk_builder):
    _size{std::move(size)}
{
    gtk_window = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), "main_window"));
    gtk_window_set_default_size(GTK_WINDOW(gtk_window), size.width, size.height);
    g_signal_connect(gtk_window, "destroy", G_CALLBACK(in_close), this);
    
    /*gtk_window_set_title(GTK_WINDOW(gtk_window), "Rudolph Software Renderer");
    gtk_window_set_resizable(GTK_WINDOW(gtk_window), TRUE);
    */
}

void MainWindow::show() {
    gtk_widget_show_all(gtk_window);
}

void MainWindow::close() {
    std::cout << "Closing...\n";
    gtk_main_quit();
}
