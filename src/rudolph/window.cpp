#include "window.h"

#include <iostream>
#include <utility>

namespace {

using namespace rudolph;
using namespace rudolph::geometry;

}

void MainWindow::show() {
    gtk_widget_show_all(window);

    gtk_main();
}

void MainWindow::close() {
    std::cout << "Closing...\n";
}
