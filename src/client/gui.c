/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** gui
*/

#include "client.h"

GdkPixbuf *get_smiley(char *name)
{
	char place[100] = "./data/smiley/";
	int size = strlen(name);

	if (name[size - 1] == '\n')
		size--;
	if (size <= 0)
		return (NULL);
	for (size_t i = 0; i < NB_SMILEY; i++) {
		if (!strcmp(name, arr_smiley[i].name)) {
			strcat(place, arr_smiley[i].pic);
			return (gdk_pixbuf_new_from_file(place, NULL));
		}
	}
	return (NULL);
}

GtkWidget *open_window(int ac, char **av)
{
	GtkWidget *window;

	gtk_init(&ac, &av);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_set_size_request(window, 600, 450);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title((GtkWindow *)window, "Cordis");
	return (window);
}

void fill_main_window(GtkWidget *window)
{
	GtkWidget *mainGrid = NULL;
	GtkWidget *topGrid = NULL;
	GtkWidget *middleGrid = NULL;

	mainGrid = gtk_table_new(10, 1, TRUE);
	gtk_container_add(GTK_CONTAINER(window), mainGrid);
	topGrid = g_m_top();
	gtk_table_attach(GTK_TABLE(mainGrid), topGrid, 0, 1, 0, 9, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 2, 2);
	middleGrid = g_m_mid();
	gtk_table_attach(GTK_TABLE(mainGrid), middleGrid, 0, 1, 9, 10, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 2, 2);
}

void start_gui(int ac, char **av)
{
	GtkWidget *window = NULL;

	window = open_window(ac, av);
	fill_main_window(window);
	gtk_widget_show_all(window);
	gtk_main();
}
