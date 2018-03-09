#include <gtk/gtk.h>
#include "rudolph/window.h"
#include "rudolph/rudolph.h"

static cairo_surface_t* surface = NULL;

static void clear_surface() {
    cairo_t* cr;

    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_destroy(cr);
}

// Create a new surface to store our scribbles
static gboolean configure_event_cb(GtkWidget* widget,
                                   GdkEventConfigure* event,
                                   gpointer data) {
    if (surface) {
        cairo_surface_destroy(surface);
    }

    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
                                                CAIRO_CONTENT_COLOR,
                                                gtk_widget_get_allocated_width(widget),
                                                gtk_widget_get_allocated_height(widget)
                                                );

    // Initialize surface to white
    clear_surface();

    return TRUE;
}

/* Redraw the screen from the surface. Note that the ::draw
 * signal receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
static gboolean draw_cb(GtkWidget* widget, cairo_t* cr, gpointer data) {
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    return FALSE;
}

/* Draw a rectangle on the surface at the given position */
static void draw_brush(GtkWidget *widget, gdouble x, gdouble y) {
    cairo_t *cr;

    /* Paint to the surface, where we store our state */
    cr = cairo_create(surface);

    cairo_rectangle(cr, x - 3, y - 3, 6, 6);
    cairo_fill(cr);

    cairo_destroy(cr);

    /* Now invalidate the affected region of the drawing area. */
    gtk_widget_queue_draw_area(widget, x - 3, y - 3, 6, 6);
}

/* Handle button press events by either drawing a rectangle
 * or clearing the surface, depending on which button was pressed.
 * The ::button-press signal handler receives a GdkEventButton
 * struct which contains this information.
 */
static gboolean button_press_event_cb(GtkWidget *widget,
                                      GdkEventButton *event,
                                      gpointer data) {
    if (surface == NULL)
        return FALSE;

    if (event->button == 1)
    {
        draw_brush(widget, event->x, event->y);
    }
    else if (event->button == 3)
    {
        clear_surface();
        gtk_widget_queue_draw(widget);
    }

    /* We've handled the event, stop processing */
    return TRUE;
}

/* Handle motion events by continuing to draw if button 1 is
 * still held down. The ::motion-notify signal handler receives
 * a GdkEventMotion struct which contains this information.
 */
static gboolean motion_notify_event_cb(GtkWidget *widget,
                                       GdkEventMotion *event,
                                       gpointer data) {
    if (surface == NULL)
        return FALSE;

    int x, y;
    GdkModifierType state;

   /* This call is very important; it requests the next motion event.
   * If you don't call gdk_window_get_pointer() you'll only get
   * a single motion event. The reason is that we specified
   * GDK_POINTER_MOTION_HINT_MASK to gtk_widget_set_events().
   * If we hadn't specified that, we could just use event->x, event->y
   * as the pointer location. But we'd also get deluged in events.
   * By requesting the next event as we handle the current one,
   * we avoid getting a huge number of events faster than we
   * can cope.
   */
    gdk_window_get_device_position(event->window, event->device, &x, &y, &state);
    // gdk_window_get_pointer(event->window, &x, &y, &state);

    if (state & GDK_BUTTON1_MASK)
        draw_brush(widget, x, y);

    /* We've handled it, stop processing */
    return TRUE;
}

static void close_window(void) {
    if (surface)
        cairo_surface_destroy(surface);

    gtk_main_quit();
}

int main(int argc, char* argv[]) {
    rudolph::main(argc, argv);
}
