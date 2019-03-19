#ifndef RUDOLPH_GRAPHIC_OBJECT_H
#define RUDOLPH_GRAPHIC_OBJECT_H

#include <string>

namespace rudolph {

class GraphicObject {
    std::string name;
    std::string type;

    virtual void draw() = 0;
};

}

#endif