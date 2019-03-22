#include "display_file.h"
#include <iostream>

namespace rudolph {

void DisplayFile::add(const std::shared_ptr<GraphicObject> object) {
    objects.push_back(object);
    std::cout << "Object added" << std::endl;
}

void DisplayFile::remove(int index) {
    objects.erase(objects.begin() + index);
    std::cout << "Object[" << index << "] removed" << std::endl;
}

void DisplayFile::replace(int index, const std::shared_ptr<GraphicObject> object) {
    objects.insert(objects.begin() + index, object);
    std::cout << "Object[" << index << "] replaced" << std::endl;
}

std::shared_ptr<GraphicObject> DisplayFile::at(int index) {
    return this->objects.at(index);
}

int DisplayFile::size() {
    return this->objects.size();
}

}