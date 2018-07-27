/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** server source files
*/

#include <irc.h>


int s_init(char *port_arg, server_t **s)
{
	int port = 0;

	if (!(*s = malloc(len(server_t)))){
		fprintf(stderr, "memory error: server_t malloc\n");
		return (-1);
	}
	(*s)->fd = -1;
	(*s)->max_fd = 3;
	(*s)->cfd = -1;
	(*s)->client = NULL;
	(*s)->channel = l_add(new_channel("ALL"), (*s)->channel);
	if (!is_number(port_arg))
		return (-1);
	port = atoi(port_arg);
	if (make_server(&port, *s) == -1)
		return (-1);
	return (1);
}

int s_run(server_t **s)
{
	client_t *head = (*s)->client;

	while (42) {
		head = (*s)->client;
		while (head) {
			send_rest(head);
			head = head->next;
		}
		if (s_catch_client(s) == 2)
			continue;
	}
	return (1);
}

int s_catch_client(server_t **serv)
{
	server_t *s = *serv;

	s_add_clients_fd(s);
	if (s_select(s) == -1)
		return (2);
	handle_fds(s);
	return (1);
}

int s_add_clients_fd(server_t *s)
{
	client_t *client = NULL;

        FD_ZERO(&s->rfds);
	for (int i = 0; i < s->max_fd + 1; i++){
		client = get_client_by_fd(s->client, i);
	        if ((client && client->is_logged) || i == s->fd)
			FD_SET(i, &s->rfds);
	}
	return (1);
}

void handle_fds(server_t *s)
{
        for (int i = 0; i < s->max_fd + 1; i++)
		accept_and_receive(s, &i);
}

