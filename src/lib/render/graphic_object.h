#ifndef RUDOLPH_GRAPHIC_OBJECT_H
#define RUDOLPH_GRAPHIC_OBJECT_H

#include <string>
#include <gtkmm.h>

namespace rudolph {

class GraphicObject {
public:
    std::string name;
    std::string type;

    virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) = 0;
};

}

#endif