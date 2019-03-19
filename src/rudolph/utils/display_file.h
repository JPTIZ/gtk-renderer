#ifndef RUDOLPH_DISPLAY_FILE_H
#define RUDOLPH_DISPLAY_FILE_H

#include <vector>
#include "graphic_object.h"

namespace rudolph {

    struct DisplayFile {
        std::vector<GraphicObject> objects;
    };

}

#endif