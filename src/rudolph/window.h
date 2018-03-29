#ifndef RUDOLPH_WINDOW_H
#define RUDOLPH_WINDOW_H

#include <memory>
#include <utility>

#include <gtk/gtk.h>

#include "render.h"
#include "geometry.h"

namespace rudolph {

template <typename Signature>
struct Event {
    using Callback = Signature*;

    std::string element_id;
    std::string event;
    void* parameters;

    Event(std::string id,
          std::string event,
          Callback callback,
          void* params):
      element_id{id},
      event{event},
      callback_{callback},
      parameters{params}
    {}

    Signature* callback() {
        return *callback_;
    }

    const Signature* callback() const {
        return *callback_;
    }

private:
    Callback callback_;
};

class MainWindow {
    using Size = geometry::Size;
public:
    MainWindow(Size);

    void show();
    void close();
    void update_list();
    void configure_gui();
    void refresh();
    void execute(const std::string&);

    Size size() const {
        return _size;
    }

    Renderer& get_renderer() {
        return renderer;
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
    Renderer renderer;
};

struct GtkInitError: std::runtime_error {
    using runtime_error::runtime_error;
};

}

#endif
