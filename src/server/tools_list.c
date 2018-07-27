/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** tools source file
*/

#include <irc.h>

int get_client_channel_id(client_t *cli, c_client_t *list)
{
	int index = -1;

	while (list) {
		index++;
		if (!strcmp(cli->name, list->client->name) && cli->fd == list->client->fd)
			return (index);
		list = list->next;
	}
	return index;
}

channel_t *get_channel_from_name(char *name, channel_t *channel)
{
	while (channel) {
		if (!strcmp(channel->c_name, name))
			return (channel);
		channel = channel->next;
	}
	return (NULL);
}

client_t *get_client_by_fd(client_t *clients, int fd)
{
	while (clients) {
		if (clients->fd == fd)
			return (clients);
		clients = clients->next;
	}
	return (NULL);
}

char *get_channel_text(channel_t *channel)
{
	char *res = NULL;
	int size = 0;
	msg_t *msg = channel->msgs;

	while (msg) {
		size += strlen(msg->msg);
		res = realloc(res, sizeof(char) * (size + 1));
		res[size] = '\0';
		strcat(res, msg->msg);
		channel = channel->next;
	}
	return (res);
}
