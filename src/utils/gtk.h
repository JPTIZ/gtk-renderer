#ifndef __UTILS_GTK_H
#define __UTILS_GTK_H

#include <gtkmm.h>

namespace utils {

template <typename WidgetType>
std::shared_ptr<WidgetType> get_widget(
        const Glib::RefPtr<Gtk::Builder> builder,
        const std::string& name)
{
    WidgetType* widget;
    builder->get_widget(name, widget);
    return std::shared_ptr<WidgetType>{widget};
}

}

#endif

