#ifndef RUDOLPH_RUDOLPH_WINDOW_H
#define RUDOLPH_RUDOLPH_WINDOW_H

#include "geometry.h"

namespace rudolph {

class MainWindow {
    using Size = geometry::Size;
public:
    MainWindow(Size size):
        _size{size}
    {}

    void show();
    void close();

    auto size() const {
        return _size;
    }

private:
    Size _size{0, 0};
};

}

#endif
