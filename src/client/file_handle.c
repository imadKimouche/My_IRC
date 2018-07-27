/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** file_handle
*/

#include "client.h"

int try_send_file(char **cmd, char *line)
{
	struct stat st;

	if (!cmd[1] || !cmd[2])
		return (0);
	if (stat(cmd[2], &st)) {
		c_input_cmd("File not found\n", &client_inf);
		return (1);
	} else if (!S_ISREG(st.st_mode)) {
		c_input_cmd("Can't send a folder\n", &client_inf);
		return (1);
	}
	client_inf.file = strdup(cmd[2]);
	c_input_cmd("Asking for file sending...\n", &client_inf);
	c_send(line);
	return (1);
}

int send_file(char **cmd, client_t *client)
{
	if (!cmd[1])
		return (1);
	if (strcmp(cmd[1], "ok\n"))
		c_input_cmd("File declined\n", client);
	else
		c_input_cmd("Sending file ...\n", client);
	return (1);
}
