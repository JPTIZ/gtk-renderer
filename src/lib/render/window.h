#ifndef RUDOLPH_RENDER_WINDOW_H
#define RUDOLPH_RENDER_WINDOW_H

#include "../algebra/matrix.h"

#include "stub2d.h"

namespace rudolph {
namespace render {

class Window {
    using Vec2 = rudolph::geometry::Vec2;
    using Size = rudolph::geometry::Size;
public:
    Window(Vec2 pos, Size size):
        _pos{pos},
        _size{size}
    {}

    const Vec2& pos() const {
        return _pos;
    }

    Vec2& pos() {
        return _pos;
    }

    const Size& size() const {
        return _size;
    }

    Size& size() {
        return _size;
    }

    void offset(const Vec2& offset) {
        _pos += offset;
    }

    void move(const Vec2& destiny) {
        _pos = destiny;
    }

    void resize(const Size& new_size) {
        _size = new_size;
    }

private:
    Vec2 _pos;
    Size _size;
};

}
}

#endif