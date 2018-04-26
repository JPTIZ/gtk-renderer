#ifndef RUDOLPH_DIALOG_H
#define RUDOLPH_DIALOG_H

#include <string>
#include <vector>

#include <gtk/gtk.h>

#include "geometry.h"
#include "window.h"

namespace rudolph {

class DialogWindow {
    using Size = geometry::Size;
public:
    DialogWindow(Size size,
                 std::string filename);

    void show();
    void close();
    void setup(std::vector<Event<void(GtkWidget*, void**)>>&& button_events);

    Size size() const {
        return _size;
    }

    template <typename Signature>
    void link_signal(const Event<Signature>& event) {
        g_signal_connect(
                GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder),
                                                  event.element_id.c_str())),
                event.event.c_str(),
                G_CALLBACK(event.callback()),
                event.parameters);
    }

private:
    Size _size{0, 0};
    GtkBuilder* gtk_builder;
    GtkWidget* gtk_window;
};

}

#endif
