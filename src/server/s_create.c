/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** s_create source file
*/

#include "irc.h"

int s_socket(server_t *s)
{
	s->fd = -1;
	s->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (s->fd == -1){
		error_handle("socket");
		return (-1);
	}
	return (1);
}

int s_bind(int *port, server_t *s)
{
	int ret = -1;

        (s->sin).sin_family = AF_INET;
	(s->sin).sin_port = htons(*port);
	(s->sin).sin_addr.s_addr = INADDR_ANY;
	ret = bind(s->fd, (sockadd_p)&(s->sin), len(s->sin));
	if (ret == -1){
		error_handle("bind");
		close(s->fd);
		return (-1);
	}
	return (1);
}

int s_listen(server_t *s)
{
	int ret = -1;

	ret = listen(s->fd, CLIENT_NUMBER);
	if (ret == -1){
		error_handle("listen");
		close(s->fd);
		return (-1);
	}
	return (1);
}

int s_accept(server_t *s)
{
	int c_fd = -1;
	int s_len = len(sockadd_t);

	c_fd = accept(s->fd, (sockadd_p)&(s->sin), (socklen_t*)&s_len);
	if (c_fd == -1){
		error_handle("accept");
		close(s->fd);
		return (-1);
	}
	return (c_fd);
}

int make_server(int *port, server_t *s)
{
	if (s_socket(s) == -1)
		return (-1);
	if (s_bind(port, s) == -1)
		return (-1);
	if (s_listen(s) == -1)
		return (-1);
	printf("[server up]\n");
	return (1);
}
