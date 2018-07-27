/*
** EPITECH PROJECT, 2018
** My ftp
** File description:
** input/output
*/

#include "irc.h"

int send_rest(client_t *client)
{
	buffer_t *buff = client->sen_b;
	int sent = 0;
	int tow = buff->read % CBUFF_SIZE + (buff->write - buff->read);

	if (!client || client->fd == -1)
		return (0);
	if (tow / CBUFF_SIZE >= 1) {
		tow = CBUFF_SIZE - (buff->read % CBUFF_SIZE);
	} else
		tow = buff->write - buff->read;
	if (buff->read < buff->write) {
		sent = write(client->fd, buff->buffer + buff->read % CBUFF_SIZE, tow);
		if (sent < 0)
			error_handle("sent");
		buff->read += sent;
	}
	return (sent);
}

int s_send(client_t *client, char *msg)
{
	buffer_t *buff = client->sen_b;

	if (!msg || !client || client->fd == -1)
		return (-1);
	for (size_t i = 0; i < strlen(msg); i++) {
		buff->buffer[buff->write % CBUFF_SIZE] = msg[i];
		buff->write++;
	}
	return (1);
}

void read_fd(client_t *client)
{
	char *tmpbuff = calloc(sizeof(char), CBUFF_SIZE + 1);
	buffer_t *buff = client->rec_b;
	int received = 0;
	int index = 0;

	received = read(client->fd, tmpbuff, CBUFF_SIZE);
	while (index != received) {
		buff->buffer[(buff->write + index) % CBUFF_SIZE] = tmpbuff[index];
		index++;
	}
	buff->write = (buff->write + received);
	free(tmpbuff);
}

char *get_inscruction(client_t *client)
{
	buffer_t *buff = client->rec_b;

	while (buff->read != buff->write) {
		buff->read++;
		buff->used_size++;
		buff->used = realloc(buff->used, buff->used_size);
		buff->used[buff->used_size - 1] = '\0';
		if (*(buff->buffer + (buff->read - 1) % CBUFF_SIZE) == '\r' &&
		    *(buff->buffer + buff->read % CBUFF_SIZE) == '\n') {
			buff->read++;
			buff->used_size = 0;
			return (strdup(buff->used));
		} else
			buff->used[buff->used_size - 1] = *(buff->buffer + (buff->read - 1) % CBUFF_SIZE);
	}
	return (NULL);
}

char *s_receive(client_t *client)
{
	if (!client)
		return (NULL);
	read_fd(client);
	return (get_inscruction(client));
}
