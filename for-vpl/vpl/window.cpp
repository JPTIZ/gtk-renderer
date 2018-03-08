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

MainWindow::MainWindow(Size size):
    _size{std::move(size)}
{
    gtk_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(gtk_window), "Rudolph Software Renderer");
    gtk_window_set_default_size(GTK_WINDOW(gtk_window), size.width, size.height);
    gtk_window_set_resizable(GTK_WINDOW(gtk_window), TRUE);
    g_signal_connect(gtk_window, "destroy", G_CALLBACK(in_close), this);
}

void MainWindow::show() {
    gtk_widget_show_all(gtk_window);
}

void MainWindow::close() {
    std::cout << "Closing...\n";
    gtk_main_quit();
}
