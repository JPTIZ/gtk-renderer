#ifndef RUDOLPH_RUDOLPH_WINDOW_H
#define RUDOLPH_RUDOLPH_WINDOW_H

#include <memory>
#include <utility>

#include <gtk/gtk.h>

#include "geometry.h"

namespace rudolph {

class MainWindow {
    using Size = geometry::Size;
public:
    MainWindow(Size size):
        _size{std::move(size)}
    {
        gtk_init(nullptr, nullptr);
        gtk_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(gtk_window), "Rudolph Software Renderer");
        gtk_window_set_resizable(GTK_WINDOW(gtk_window), TRUE);
        auto close = []() {
        };
        g_signal_connect(gtk_window, "destroy", G_CALLBACK(close), this);
    }

    void show();
    void close();

    auto size() const {
        return _size;
    }

private:
    Size _size{0, 0};
    GtkWidget* gtk_window;
};

}

#endif
