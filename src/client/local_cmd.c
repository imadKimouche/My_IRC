/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** input_cmd
*/

#include "client.h"

static int view_write(void *data)
{
	GtkTextBuffer *buffer = NULL;
	GtkTextIter iter;
	GdkPixbuf * pixbuf = NULL;
	char **split_res = NULL;
	char *lines = (char *)data;

	split_res = split(lines, " ");
	buffer = gtk_text_view_get_buffer(client_inf.window.textView);
	gtk_text_buffer_get_end_iter(buffer, &iter);
	gtk_text_buffer_insert(buffer, &iter, split_res[0], -1);
	for (int i = 1; split_res[i]; i++) {
		gtk_text_buffer_get_end_iter(buffer, &iter);
		gtk_text_buffer_insert(buffer, &iter, " ", 1);
		gtk_text_buffer_get_end_iter(buffer, &iter);
		pixbuf = get_smiley(strdup(split_res[i]));
		if (pixbuf)
			gtk_text_buffer_insert_pixbuf(buffer, &iter, pixbuf);
		else
			gtk_text_buffer_insert(buffer, &iter, split_res[i], -1);
	}
	return (0);
}

void c_input_cmd(char *lines, client_t *client)
{
	int size = strlen(lines);

	if (!client->window.textView || !lines)
		return;
	lines = realloc(lines, sizeof(char) * (strlen(lines) + 2));
	if (!lines)
		return;
	lines[size - 1] = ' ';
	lines[size] = '\n';
	lines[size + 1] = '\0';
	gdk_threads_add_idle(view_write, lines);
}
