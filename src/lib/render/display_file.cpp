#include "display_file.h"
#include <iostream>

namespace rudolph {

void DisplayFile::add(std::shared_ptr<GraphicObject> object) {
    std::cout << "Objeto adicionado" << std::endl;
    objects.push_back(object);
}

void DisplayFile::remove_from(int index) {
    (void)index;
}

void DisplayFile::replace(int index, std::shared_ptr<GraphicObject> object) {
    (void)index;
    (void)object;
}

std::shared_ptr<GraphicObject> DisplayFile::at(int index) {
    return objects.at(index);
}

int DisplayFile::size() {
    return objects.size();
}

}
