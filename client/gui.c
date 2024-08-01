#include <gtk/gtk.h>
#include <mosquitto.h>

// Callback per il pulsante di connessione
void on_connect_button_clicked(GtkButton *button, gpointer user_data) {
    const char *broker = gtk_entry_get_text(GTK_ENTRY(user_data));
    // Logica per connettersi al broker
}

// Callback per il pulsante di pubblicazione
void on_publish_button_clicked(GtkButton *button, gpointer user_data) {
    const char *message = gtk_entry_get_text(GTK_ENTRY(user_data));
    // Logica per pubblicare il messaggio
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *broker_entry;
    GtkWidget *connect_button;
    GtkWidget *publish_entry;
    GtkWidget *publish_button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mosquitto Client");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    broker_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(broker_entry), "Enter broker address");
    gtk_grid_attach(GTK_GRID(grid), broker_entry, 0, 0, 1, 1);

    connect_button = gtk_button_new_with_label("Connect");
    g_signal_connect(connect_button, "clicked", G_CALLBACK(on_connect_button_clicked), broker_entry);
    gtk_grid_attach(GTK_GRID(grid), connect_button, 1, 0, 1, 1);

    publish_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(publish_entry), "Enter message");
    gtk_grid_attach(GTK_GRID(grid), publish_entry, 0, 1, 1, 1);

    publish_button = gtk_button_new_with_label("Publish");
    g_signal_connect(publish_button, "clicked", G_CALLBACK(on_publish_button_clicked), publish_entry);
    gtk_grid_attach(GTK_GRID(grid), publish_button, 1, 1, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

