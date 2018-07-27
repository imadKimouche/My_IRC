/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** client_cmd source file
*/

#include "irc.h"


void c_nick(client_t* client, char **cmd, server_t *server)
{
	char *reply = NULL;

	if (cmd[0]){
		if (!cmd[1]){
			s_send(client, ":server 431 :No nickname given\r\n");
			return;
		}
		else if (!valid_nick(server->client, cmd[1])){
			asprintf(&reply, "%s%s%s", ":server 433 ",
				 cmd[1], " :Nickname is already in use\r\n");
			s_send(client, reply);
			return;
		}
		if (!register_client(client, cmd[1]))
			return;
		client->name = strdup(cmd[1]);
	}
}

void display_channel_clients(channel_t *channel, char *c_name, client_t* client)
{
	c_client_t *c_clients = NULL;

	while (channel){
		if (!(strcmp(channel->c_name, c_name))){
			c_clients = channel->clients;
			while (c_clients){
				s_send(c_clients->client,
				(c_clients->client)->name);
				s_send(client, "\n");
				c_clients = c_clients->next;
			}
		}
		channel = channel->next;
	}
}

void c_names(client_t* client, char **cmd, server_t *server)
{
	channel_t *channel = server->channel;

	if (!cmd[1])
		display_channel_clients(channel, "ALL", client);
	else
		display_channel_clients(channel, cmd[1], client);
}

int get_client_fd(client_t *clients, char *nickname)
{
	while (clients){
		if (!(strcmp(clients->name, nickname)))
			return (clients->fd);
		clients = clients->next;
	}
	return (-1);
}

void count_letters(int *count, int *whites, char **cmd)
{
	while (*cmd){
		count += strlen(*cmd);
		cmd++;
		whites++;
	}
	whites++;
}

