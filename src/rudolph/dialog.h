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
    void setup();

    Size size() const {
        return _size;
    }

private:
    Size _size{0, 0};
    GtkBuilder* gtk_builder;
    GtkWidget* gtk_window;
};

}

#endif
