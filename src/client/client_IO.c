/*
** EPITECH PROJECT, 2018
** My ftp
** File description:
** input/output
*/

#include "client.h"

int c_send(char *msg)
{
	int size = 0;
	int sent = 0;

	if (!msg || client_inf.fd == -1)
		return (-1);
	size = strlen(msg);
	msg = realloc(msg, size + 3);
	msg[size] = '\r';
	msg[size + 1] = '\n';
	msg[size + 2] = '\0';
	size += 2;
	while (sent < size) {
		sent += write(client_inf.fd, msg + sent, size - sent);
	}
	return (sent);
}

char *c_receive(void)
{
	int buff_size = 1000;
	char *buff = calloc(sizeof(char), buff_size);

	if (client_inf.fd == -1)
		return (NULL);
	if (read(client_inf.fd, buff, buff_size - 1)) {
		return (buff);
	}
	return (NULL);
}

void c_socket(void)
{
	int fd = -1;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		error_handle("Client: socket");
	client_inf.fd = fd;
}

void c_connect(int port, char *addr)
{
	sockadd_t sin;
	int s_len = sizeof(sockadd_t);

	if (port < 0 || port > 80000)
		error_handle("Client: Wrong port.\n");
	sin.sin_addr.s_addr = inet_addr(addr);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	c_socket();
	if (connect(client_inf.fd, (sockadd_p)&sin, (socklen_t)s_len))
		error_handle("Client: connect");
}

void c_disconnect(void)
{
	if (client_inf.fd != -1) {
		if (!close(client_inf.fd))
			error_handle("Client: disconnect");
		client_inf.fd = -1;
	}
}
