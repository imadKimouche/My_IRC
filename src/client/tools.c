/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** tools
*/

#include "client.h"

char **split(char *line, char *delimiters)
{
	char *tok = NULL;
	char **res = NULL;
	int nb = 0;

	tok = strtok(strdup(line), delimiters);
	while (tok != NULL) {
		res = realloc(res, sizeof(char *) * (++nb));
		res[nb - 1] = malloc(sizeof(char) * strlen(tok));
		res[nb - 1] = tok;
		tok = strtok(NULL, delimiters);
	}
	res = realloc(res, sizeof(char *) * (++nb));
	res[nb - 1] = NULL;
	return (res);
}

gchar *c_get_text(GtkEntry *textType)
{
	GtkEntryBuffer *buffer = gtk_entry_get_buffer(textType);
	gchar *text;

	text = strdup(gtk_entry_buffer_get_text(buffer));
	gtk_entry_buffer_delete_text(buffer, 0, -1);
	return (text);
}

int check_cmd(char *line)
{
	char **cmd = NULL;

	if (!line)
		return (0);
	cmd = split(strdup(line), " ");
	if (!strcmp(cmd[0], "/file"))
		return try_send_file(cmd, line);
	return (0);
}

void handle_input_cmd(void)
{
	gchar *res = c_get_text(client_inf.window.textType);

	if (*res != '\0') {
		if (!check_cmd(res))
			c_send(res);
	}
}

void handle_output_cmd(char *lines, client_t *client)
{
	char **cmd = NULL;

	if (!lines)
		return;
	cmd = split(strdup(lines), " ");
	if (!cmd || cmd[0] == NULL)
		return;
	if (!strncmp(cmd[0], "file:", 5))
		send_file(cmd, client);
	else
		c_input_cmd(lines, client);
}
