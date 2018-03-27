#include "window.h"

#include "objects/shapes.h"
#include <iostream>
#include <utility>

namespace rudolph {

using namespace rudolph::objects;
using Size = geometry::Size;

void on_close(GtkWidget* btn, gpointer* data) {
    reinterpret_cast<MainWindow*>(data)->close();
}

GtkWidget* create_gtk_window(GtkBuilder* gtk_builder, Size size) {
    auto err = (GError*)nullptr;
    if (not gtk_builder_add_from_file(gtk_builder, "mainwindow.ui", &err)) {
        throw GtkInitError(
                std::string{"failed to initialize main window from UI file: "} +
                err->message + "\n");
    }

    auto pre_window = gtk_builder_get_object(gtk_builder, "main_window");
    auto gtk_window = GTK_WIDGET(pre_window);
    gtk_window_set_default_size(GTK_WINDOW(gtk_window), size.width, size.height);
    gtk_window_set_title(GTK_WINDOW(gtk_window), "Rudolph Software Rendeer");

    return gtk_window;
}

GtkWidget* get_component(GtkBuilder* gtk_builder, std::string id) {
    return GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), id.c_str()));
}

void on_btn_up(GtkWidget *widget, gpointer* data) {
    std::cout << "btn up" << std::endl;
    auto& r = reinterpret_cast<MainWindow*>(data)->get_renderer();
    auto& rt = r.render_target();
    rt.move_camera(0, -1);
}

void on_btn_down(GtkWidget *widget, gpointer* data) {
    std::cout << "btn down" << std::endl;
    auto& r = reinterpret_cast<MainWindow*>(data)->get_renderer();
    auto& rt = r.render_target();
    rt.move_camera(0, 1);
}

void on_btn_left(GtkWidget *widget, gpointer* data) {
    std::cout << "btn left" << std::endl;
    auto& r = reinterpret_cast<MainWindow*>(data)->get_renderer();
    auto& rt = r.render_target();
    rt.move_camera(1, 0);
}

void on_btn_right(GtkWidget *widget, gpointer* data) {
    std::cout << "btn right" << std::endl;
    auto& r = reinterpret_cast<MainWindow*>(data)->get_renderer();
    auto& rt = r.render_target();
    rt.move_camera(-1, 0);
}

void on_btn_in(GtkWidget *widget, gpointer* data) {
    std::cout << "btn in" << std::endl;
    auto& r = reinterpret_cast<MainWindow*>(data)->get_renderer();
    auto& rt = r.render_target();
    rt.zoom(reinterpret_cast<MainWindow*>(data)->step()/100);
}

void on_btn_out(GtkWidget *widget, gpointer data) {
    std::cout << "btn out" << std::endl;
    auto& r = reinterpret_cast<MainWindow*>(data)->get_renderer();
    auto& rt = r.render_target();
    rt.zoom(-reinterpret_cast<MainWindow*>(data)->step());
}

void on_btn_new(GtkWidget *widget, gpointer data) {
    std::cout << "btn new" << std::endl;
}

void on_btn_edit(GtkWidget *widget, gpointer data) {
    std::cout << "btn edit" << std::endl;
}

void on_btn_del(GtkWidget *widget, gpointer data) {
    std::cout << "btn del" << std::endl;
}

MainWindow::MainWindow(Size size):
    _size{size},
    gtk_builder{gtk_builder_new()},
    gtk_window(create_gtk_window(gtk_builder, _size)),
    renderer{get_component(gtk_builder, "canvas")}
{
    g_signal_connect(gtk_window, "destroy", G_CALLBACK(on_close), this);

    configure_gui();
}

void MainWindow::configure_gui()
{
    // Signals for each and every button
    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_up"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_up), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_down"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_down), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_left"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_left), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_right"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_right), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_in"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_in), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_out"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_out), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_new"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_new), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_edit"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_edit), this);

    button = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), "btn_del"));
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_del), this);
}

void MainWindow::show() {
    gtk_widget_show_all(gtk_window);

    renderer.add_object(Point{10, 10});
    renderer.add_object(Line{100, 20, 110, 30});
    renderer.add_object(Line{300, 400, 200, 380});
    renderer.add_object(Point{320, 420});
    auto points = std::vector<Point2D>{
        Point2D{150, 150},
        Point2D{175, 175},
        Point2D{160, 200},
        Point2D{140, 200},
        Point2D{125, 175},
    };
    renderer.add_object(Polygon(points));

    update_list();

}

void MainWindow::update_list() {
    auto list = (GtkListStore*)get_component(gtk_builder, "list_store");
    auto iter = GtkTreeIter{};
    for (auto obj: renderer.display_file()) {
        auto name = obj.name();
        gtk_list_store_append(list, &iter);
        gtk_list_store_set(list, &iter, 0, name.c_str(), -1);
    }
}

void MainWindow::close() {
    gtk_main_quit();
}

}
