/*
** EPITECH PROJECT, 2018
** My ftp
** File description:
** server cmd
*/

#include "irc.h"

void s_list(client_t *client, char **cmd, server_t *server)
{
	channel_t *channel = server->channel;
	char *result = NULL;

	if (!client || !cmd || !cmd[0])
		return;
	if (!cmd[1]) {
		while (channel != NULL) {
			add_str(&result, ":server 322 ");
			add_str(&result, channel->c_name);
			add_str(&result, " : No topic was set\n");
			channel = channel->next;
		}
	} else {
		while (channel != NULL) {
			if (strstr(channel->c_name, cmd[1])) {
				add_str(&result, ":server 322 ");
				add_str(&result, channel->c_name);
				add_str(&result, " : No topic was set\n");
			}
			channel = channel->next;
		}
		add_str(&result, "\r\n");
	}
	s_send(client, ":server 321 Channel :Users  Name\r\n");
	s_send(client, result);
	s_send(client, ":server 323 :End of /LIST\r\n");
}

void s_join_channel(client_t *client, char **cmd, server_t *server)
{
	channel_t *channel = NULL;
	c_client_t *clic = NULL;

	if (!cmd[1]) {
		s_send(client, ":server 461 /join :Not enough parameters\r\n");
		return;
	}
	channel = get_channel_from_name(cmd[1], server->channel);
	if (!channel){
		channel = new_channel(cmd[1]);
		server->channel = l_add(channel, server->channel);
	}
	clic = new_channel_client(client);
	s_part_channel(client, cmd, server);
	channel->clients = l_add(clic, channel->clients);
	client->channel = channel;
	s_send(client, ":server 666 /join : sclean \r\n");
	s_send(client, get_channel_text(channel));
	s_send(client, "\r\n");
}

int get_channel_id_by_name(server_t *server, char *name)
{
	channel_t *channel = NULL;
	int id = 0;

	channel = server->channel;
	while (channel) {
		if (!strcmp(name, channel->c_name))
			return (id);
		id++;
		channel = channel->next;
	}
	return (-1);
}

void s_part_channel(client_t *client, char **cmd, server_t *server)
{
	int id = -1;
	int c_id = -1;

	unused(cmd);
	if (client->channel)
		id = get_client_channel_id(client, client->channel->clients);
	if (id > 0) {
		l_remove((void**)&(client->channel->clients), id);
		client->channel = NULL;
	}
	else if (id == 0) {
		c_id = get_channel_id_by_name(server, client->channel->c_name);
		if (c_id != -1)
			l_remove((void**)&(server->channel), c_id);
	}
}

void s_users(client_t *client, char **cmd, server_t *server)
{
	client_t *cli = server->client;
	char *result = NULL;
	char reply[1024];

	unused(cmd);
	unused(client);
	while (cli) {
		result = add_str(&result, cli->name);
		add_str(&result, " ");
		cli = cli->next;
	}
	sprintf(reply, "%s%s\r\n", ":server 393 ", result);
	s_send(client, ":server 392 :UserID Terminal  Host\r\n");
	s_send(client, reply);
	s_send(client, ":server  394 :End of users\r\n");
}
