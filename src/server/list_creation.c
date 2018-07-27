/*
** EPITECH PROJECT, 2018
** My ftp
** File description:
** list creation
*/

#include "irc.h"

channel_t *new_channel(char *name)
{
	channel_t *tmp = malloc(sizeof(channel_t));

	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->msgs = NULL;
	asprintf(&tmp->c_name, "%s%s", "#", name);
	tmp->clients = NULL;
	return (tmp);
}

p_msg_t *new_pmsg(char *name)
{
	p_msg_t *tmp = malloc(sizeof(p_msg_t));

	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->name = name;
	tmp->msgs = NULL;
	return (tmp);
}

msg_t *new_msg(client_t *client, char *msg)
{
	msg_t *tmp = malloc(sizeof(msg_t));

	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->client = client;
	tmp->msg = msg;
	return (tmp);
}

c_client_t *new_channel_client(client_t *client)
{
	c_client_t *tmp = malloc(sizeof(c_client_t));

	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->client = client;
	return (tmp);
}

client_t *new_client(int fd, channel_t *channel)
{
	client_t *tmp = calloc(sizeof(client_t), 1);
	buffer_t *sen_b = calloc(sizeof(buffer_t), 1);
	buffer_t *rec_b = calloc(sizeof(buffer_t), 1);

	sen_b->buffer = calloc(sizeof(char), CBUFF_SIZE);
	sen_b->write = 0;
	sen_b->read = 0;
	rec_b->buffer = calloc(sizeof(char), CBUFF_SIZE);
	rec_b->write = 0;
	rec_b->read = 0;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->fd = fd;
	tmp->name = "Anonymous";
	tmp->is_logged = 1;
	tmp->is_registered = 0;
	tmp->p_msg = NULL;
	tmp->channel = channel;
	tmp->sen_b = sen_b;
	tmp->rec_b = rec_b;
	return (tmp);
}
