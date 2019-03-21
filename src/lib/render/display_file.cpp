#include "display_file.h"
#include <iostream>

namespace rudolph {

void DisplayFile::add(std::shared_ptr<GraphicObject> object) {
    std::cout << "Objeto adicionado" << std::endl;
    this->objects.push_back(object);
}

void DisplayFile::remove_from(int index) {

}

void DisplayFile::replace(int index, std::shared_ptr<GraphicObject> object) {

}

std::shared_ptr<GraphicObject> DisplayFile::at(int index) {
    return this->objects.at(index);
}

int DisplayFile::size() {
    return this->objects.size();
}

}