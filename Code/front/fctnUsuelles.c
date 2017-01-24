#include "../headers/fctnUsuelles.h"

void popupMessage(const char* titre, const char* message, GtkWidget* parent)
{
    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    // Create the widgets
    flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons (titre, GTK_WINDOW(parent), flags,
                                           "OK", GTK_RESPONSE_NONE, NULL);

    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new(message);

    // Ensure that the dialog box is destroyed when the user responds
    g_signal_connect_swapped (dialog, "response",
                              G_CALLBACK (gtk_widget_destroy), dialog);
    gtk_container_add (GTK_CONTAINER (content_area), label);
    gtk_widget_show_all(dialog);
}
