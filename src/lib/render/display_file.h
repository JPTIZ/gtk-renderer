#ifndef RUDOLPH_DISPLAY_FILE_H
#define RUDOLPH_DISPLAY_FILE_H

#include <vector>
#include "graphic_object.h"

namespace rudolph {

    struct DisplayFile {
        std::vector<std::shared_ptr<GraphicObject>> objects;

        void add(std::shared_ptr<GraphicObject> object);

        void remove_from(int index);

        void replace(int index, std::shared_ptr<GraphicObject> object);

        std::shared_ptr<GraphicObject> at(int index);

        int size();
    };

}

#endif