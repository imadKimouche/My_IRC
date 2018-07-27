/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** gui_w_main
*/

#include "client.h"

GtkWidget *g_m_top(void)
{
	GtkWidget *textView = NULL;
	GtkWidget *grid = NULL;
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);

	grid = gtk_table_new(1, 1, TRUE);
	textView = gtk_text_view_new();
	client_inf.window.textView = (GtkTextView*) textView;
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow *)scrolled_window,
					      textView);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
	gtk_text_view_set_editable((GtkTextView*) textView, FALSE);
	gtk_text_view_set_cursor_visible((GtkTextView*) textView, FALSE);
	c_start_input_captation(&client_inf);
	gtk_table_attach(GTK_TABLE(grid), scrolled_window, 0, 1, 0, 1,
			 GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 2, 2);
	return (grid);
}

GtkWidget *g_m_mid()
{
	GtkWidget *textType = NULL;
	GtkWidget *send = NULL;
	GtkWidget *sendFile = NULL;
	GtkWidget *grid = NULL;

	grid = gtk_table_new(1, 10, TRUE);
	sendFile = gtk_button_new_with_label("File");
	gtk_table_attach(GTK_TABLE(grid), sendFile, 0, 1, 0, 1,
			 GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 2, 2);
	g_signal_connect(sendFile, "clicked", G_CALLBACK(a_send), NULL);
	textType = gtk_entry_new();
	client_inf.window.textType = (GtkEntry*) textType;
	gtk_table_attach(GTK_TABLE(grid), textType, 1, 8, 0, 1,
			 GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
	g_signal_connect(textType, "activate", G_CALLBACK(a_send), NULL);
	send = gtk_button_new_with_label("Send");
	gtk_table_attach(GTK_TABLE(grid), send, 8, 10, 0, 1,
			 GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 2, 2);
	g_signal_connect(send, "clicked", G_CALLBACK(a_send), NULL);
	return (grid);
}
