#include "window.h"

#include "objects/shapes.h"
#include <iostream>
#include <utility>

namespace rudolph {

using namespace rudolph::objects;
using Size = geometry::Size;

void on_close(GtkWidget* btn, gpointer* data) {
    reinterpret_cast<MainWindow*>(data)->close();
}

GtkWidget* create_gtk_window(GtkBuilder* gtk_builder, Size size) {
    auto err = static_cast<GError*>(nullptr);
    if (not gtk_builder_add_from_file(gtk_builder, "mainwindow.ui", &err)) {
        throw GtkInitError(
                std::string{"failed to initialize main window from UI file: "} +
                err->message + "\n");
    }

    auto pre_window = gtk_builder_get_object(gtk_builder, "main_window");
    auto gtk_window = GTK_WIDGET(pre_window);
    gtk_window_set_default_size(GTK_WINDOW(gtk_window), size.width, size.height);
    gtk_window_set_title(GTK_WINDOW(gtk_window), "Rudolph Software Rendeer");

    auto window = gtk_builder_get_object(gtk_builder, "main_window");

    return gtk_window;
}

GtkWidget* get_component(GtkBuilder* gtk_builder, std::string id) {
    return GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtk_builder), id.c_str()));
}

void update_window_size(GtkWidget* widget, gpointer* data) {
    auto& window = *reinterpret_cast<MainWindow*>(data);
    window.refresh();
}

void on_btn_out(GtkWidget *widget, gpointer* data) {
    auto& r = *reinterpret_cast<Renderer*>(data);
}

bool update_tree_selection(GtkTreeView*& tree,
                           GtkTreeSelection*& selection,
                           GdkEventButton*& event) {
    GtkTreePath* path;
    GtkTreeViewColumn* column;

    if (not gtk_tree_view_get_path_at_pos(tree,
                                          event->x, event->y,
                                          &path,
                                          &column,
                                          nullptr,
                                          nullptr)) {
        return false;
    }

    if (column != gtk_tree_view_get_column(tree, 0)) {
        gtk_tree_path_free(path);
        return false;
    }

    gtk_tree_selection_unselect_all(selection);
    gtk_tree_selection_select_path(selection, path);
    gtk_tree_path_free(path);

    return true;
}

std::string extract_tree_value(GtkTreeModel* model,
                               GtkTreeIter& iter) {
    char* value;
    gtk_tree_model_get(model, &iter, 0, &value, -1);
    auto str = std::string{value};
    g_free(value);
    return str;
}

void show_popup(GtkTreeView*& tree,
                GtkMenu*& popup,
                GtkTreeSelection*& selection,
                gpointer* data)
{
    GtkTreeIter iter;
    GtkTreeModel* model;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        auto value = extract_tree_value(model, iter);
    }

    gtk_menu_popup_at_pointer(popup, nullptr);
}

bool on_mouse_press(GtkWidget* widget, GdkEventButton* event, gpointer* data) {
    auto tree = GTK_TREE_VIEW(widget);
    auto popup = GTK_MENU(reinterpret_cast<GMenu*>(data));

    if (event->type == GDK_BUTTON_PRESS and event->button == 3) {
        auto selection = gtk_tree_view_get_selection(tree);

        if (not update_tree_selection(tree, selection, event)) {
            return false;
        }

        show_popup(tree, popup, selection, data);

        return true;
    }
    return false;
}

std::string gtkentry_value(GtkBuilder* builder, const std::string& id) {
    return gtk_entry_get_text(
            reinterpret_cast<GtkEntry*>(get_component(builder, id))
    );
}

MainWindow::MainWindow(Size size):
    _size{size},
    gtk_builder{gtk_builder_new()},
    gtk_window(create_gtk_window(gtk_builder, _size)),
    renderer{get_component(gtk_builder, "canvas")}
{
    g_signal_connect(gtk_window, "destroy", G_CALLBACK(on_close), this);
    g_signal_connect(get_component(gtk_builder, "treeview1"),
                     "button-press-event", G_CALLBACK(on_mouse_press),
                     GTK_MENU(get_component(gtk_builder, "displayfile_popup")));

    configure_gui();
}

void MainWindow::execute(const std::string& cmd) {
    std::cout << cmd << std::endl;
}

void MainWindow::configure_gui()
{
    auto button_events = std::vector<Event<void(GtkWidget*, void**)>>{
        {"btn_up", "clicked",
            [](GtkWidget* w, gpointer* data) {
                auto& r = *reinterpret_cast<Renderer*>(data);
                auto& rt = r.render_target();
                rt.move_camera(0, -10);
            }, &renderer},
        {"btn_down", "clicked",
            [](GtkWidget* w, gpointer* data) {
                auto& r = *reinterpret_cast<Renderer*>(data);
                auto& rt = r.render_target();
                rt.move_camera(0, 10);
            }, &renderer},
        {"btn_left", "clicked",
            [](GtkWidget* w, gpointer* data) {
                auto& r = *reinterpret_cast<Renderer*>(data);
                auto& rt = r.render_target();
                rt.move_camera(10, 0);
            }, &renderer},
        {"btn_right", "clicked",
            [](GtkWidget* w, gpointer* data) {
                auto& r = *reinterpret_cast<Renderer*>(data);
                auto& rt = r.render_target();
                rt.move_camera(-10, 0);
            }, &renderer},
        {"btn_in", "clicked",
            [](GtkWidget* w, gpointer* data) {
                auto& r = *reinterpret_cast<Renderer*>(data);
                auto& rt = r.render_target();
                rt.zoom(0.1);
            }, &renderer},
        {"btn_out", "clicked",
            [](GtkWidget* w, gpointer* data) {
                auto& _this = *reinterpret_cast<MainWindow*>(data);
                auto& rt = _this.renderer.render_target();
                rt.zoom(-0.1);
            }, this},
        {"btn_new", "clicked",
            [](GtkWidget* w, gpointer* data) {
                std::cout << "btn new\n";
            }, &renderer},
        {"btn_edit", "clicked",
            [](GtkWidget* w, gpointer* data) {
                std::cout << "btn edit\n";
            }, &renderer},
        {"btn_del", "clicked",
            [](GtkWidget* w, gpointer* data) {
                std::cout << "btn del\n";
            }, &renderer},
        {"btn_update_window", "clicked", update_window_size, this},
        {"btn_exec_cmdline", "clicked",
            [](GtkWidget* w, gpointer* data) {
                reinterpret_cast<MainWindow*>(data)->execute("print yay");
            }, this},
    };

    for (auto event: button_events) {
        std::cout << "linking " << event.element_id << std::endl;
        link_signal(event);
        std::cout << "done!" << event.element_id << std::endl;
    }

    gtk_entry_set_text(GTK_ENTRY(get_component(gtk_builder, "edt_window_width")), "800");
    gtk_entry_set_text(GTK_ENTRY(get_component(gtk_builder, "edt_window_height")), "600");
    update_window_size(nullptr, (void**)this);
}

void MainWindow::show() {
    gtk_widget_show_all(gtk_window);

    renderer.add_object(Point{10, 10});
    renderer.add_object(Line{100, 20, 110, 30});
    renderer.add_object(Line{300, 400, 200, 380});
    renderer.add_object(Point{320, 420});
    auto points = std::vector<Point2D>{
        Point2D{150, 150},
        Point2D{175, 175},
        Point2D{160, 200},
        Point2D{140, 200},
        Point2D{125, 175},
    };
    renderer.add_object(Polygon(points));

    update_list();

}

void MainWindow::refresh() {
    auto window_size = Size{
        std::stoi(gtkentry_value(gtk_builder, "edt_window_width")),
        std::stoi(gtkentry_value(gtk_builder, "edt_window_height"))
    };
    renderer.render_target().window().resize(window_size);
}

void MainWindow::update_list() {
    auto list = GTK_LIST_STORE(get_component(gtk_builder, "list_store"));
    auto iter = GtkTreeIter{};
    for (auto obj: renderer.display_file()) {
        auto name = obj.name();
        gtk_list_store_append(list, &iter);
        gtk_list_store_set(list, &iter, 0, name.c_str(), -1);
    }
}

void MainWindow::close() {
    gtk_main_quit();
}

}
