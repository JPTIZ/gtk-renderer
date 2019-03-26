#ifndef RUDOLPH_DISPLAY_FILE_H
#define RUDOLPH_DISPLAY_FILE_H

#include <vector>
#include "graphic_object.h"

namespace rudolph {

class DisplayFileColumns : public Gtk::TreeModel::ColumnRecord {
public:
    DisplayFileColumns() {
        add(m_col_name);
        add(m_col_type);
    };

    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_type;
};

struct DisplayFile {
    std::vector<std::shared_ptr<GraphicObject>> objects;

    void add(const std::shared_ptr<GraphicObject> object);

    void remove(int index);

    void replace(int index, const std::shared_ptr<GraphicObject> object);

    std::shared_ptr<GraphicObject> at(int index);

    int size();
};

}

#endif