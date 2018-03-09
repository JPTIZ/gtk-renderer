#include "window.h"

#include "objects/shapes.h"

#include <utility>

namespace {

using namespace rudolph;
using namespace rudolph::geometry;

void in_close(GtkWidget* btn, gpointer* data) {
    reinterpret_cast<MainWindow*>(data)->close();
}

struct GtkInitError: std::runtime_error {
    using runtime_error::runtime_error;
};

GtkWidget* create_gtk_window(GtkBuilder* gtk_builder, Size size) {
    GError* err = nullptr;
    if (not gtk_builder_add_from_file(gtk_builder, "mainwindow.ui", &err)) {
        throw GtkInitError(
                std::string{"failed to initialize main window from UI file: "} +
                err->message + "\n");
    }

    auto bar = gtk_builder_get_object(gtk_builder, "main_window");
    auto gtk_window = GTK_WIDGET(bar);
    gtk_window_set_default_size(GTK_WINDOW(gtk_window), size.width, size.height);
    gtk_window_set_title(GTK_WINDOW(gtk_window), "Rudolph Software Renderer");

    return gtk_window;
}

GtkWidget* get_component(GtkBuilder* gtk_builder, std::string id) {
    return GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), id.c_str()));
}

}

MainWindow::MainWindow(Size size):
    _size{size},
    gtk_builder{gtk_builder_new()},
    gtk_window(create_gtk_window(gtk_builder, _size)),
    renderer{get_component(gtk_builder, "canvas")}
{
    g_signal_connect(gtk_window, "destroy", G_CALLBACK(in_close), this);
}

void MainWindow::show() {
    gtk_widget_show_all(gtk_window);
    using namespace objects;
    renderer.add_object(Point{10, 10});
    renderer.add_object(Line{100, 20, 110, 30});
    auto points = std::vector<Point2D>{
        Point2D{150, 150},
        Point2D{175, 175},
        Point2D{160, 200},
        Point2D{140, 200},
        Point2D{125, 175},
    };
    renderer.add_object(Polygon(points));
}

void MainWindow::close() {
    gtk_main_quit();
}
