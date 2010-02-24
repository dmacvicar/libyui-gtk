/********************************************************************
 *           YaST2-GTK - http://en.opensuse.org/YaST2-GTK           *
 ********************************************************************/

/* YGtkScrolledWindow extends GtkScrolledWindow adding the possibility to add
   a widget in the corner between the scrollbars, flowing into the vertical
   scroll bar (which is why the policy should be ALWAYS for the vertical bar).
*/

#ifndef YGTK_SCROLLED_WINDOW_H
#define YGTK_SCROLLED_WINDOW_H

#include <gtk/gtkscrolledwindow.h>
G_BEGIN_DECLS

#define YGTK_TYPE_SCROLLED_WINDOW            (ygtk_scrolled_window_get_type ())
#define YGTK_SCROLLED_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
	YGTK_TYPE_SCROLLED_WINDOW, YGtkScrolledWindow))
#define YGTK_SCROLLED_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  \
	YGTK_TYPE_SCROLLED_WINDOW, YGtkScrolledWindowClass))
#define YGTK_IS_SCROLLED_WINDOW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                                              YGTK_TYPE_SCROLLED_WINDOW))
#define YGTK_IS_SCROLLED_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  \
                                              YGTK_TYPE_SCROLLED_WINDOW))
#define YGTK_SCROLLED_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  \
	YGTK_TYPE_SCROLLED_WINDOW, YGtkScrolledWindowClass))

typedef struct _YGtkScrolledWindow
{
	GtkScrolledWindow parent;
	//members:
	GtkWidget *corner_child;
} YGtkScrolledWindow;

typedef struct _YGtkScrolledWindowClass
{
	GtkScrolledWindowClass parent_class;
} YGtkScrolledWindowClass;

GtkWidget* ygtk_scrolled_window_new (void);
GType ygtk_scrolled_window_get_type (void) G_GNUC_CONST;

// container_add/remove combo
void ygtk_scrolled_window_replace (YGtkScrolledWindow *scroll, GtkWidget *child);

void ygtk_scrolled_window_set_corner_widget (YGtkScrolledWindow *scroll,
                                             GtkWidget *widget);

G_END_DECLS
#endif /*YGTK_SCROLLED_WINDOW_H*/

/* YGtkTreeView hacks support for a right-click signal.
*/

#ifndef YGTK_TREE_VIEW_H
#define YGTK_TREE_VIEW_H

#include <gtk/gtktreeview.h>
G_BEGIN_DECLS

#define YGTK_TYPE_TREE_VIEW            (ygtk_tree_view_get_type ())
#define YGTK_TREE_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
	YGTK_TYPE_TREE_VIEW, YGtkScrolledWindow))
#define YGTK_TREE_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  \
	YGTK_TYPE_TREE_VIEW, YGtkScrolledWindowClass))
#define YGTK_IS_TREE_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                                              YGTK_TYPE_TREE_VIEW))
#define YGTK_IS_TREE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  \
                                              YGTK_TYPE_TREE_VIEW))
#define YGTK_TREE_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  \
	YGTK_TYPE_TREE_VIEW, YGtkScrolledWindowClass))

typedef struct _YGtkTreeView
{
	GtkTreeView parent;
} YGtkTreeView;

typedef struct _YGtkTreeViewClass
{
	GtkTreeViewClass parent_class;

	// signals:
	void (*right_click) (YGtkTreeView *view, gboolean outreach);
} YGtkTreeViewClass;

GtkWidget* ygtk_tree_view_new (void);
GType ygtk_tree_view_get_type (void) G_GNUC_CONST;

void ygtk_tree_view_popup_menu (YGtkTreeView *view, GtkWidget *menu);

G_END_DECLS
#endif /*YGTK_TREE_VIEW_H*/
