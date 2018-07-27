/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** client cmd 3
*/

#include "irc.h"

char *reform(char **cmd)
{
	char *ret = NULL;
	int whites = 0;
	int count = 0;

	count_letters(&count, &whites, cmd);
	if (!(ret = malloc(len(char) * (count + whites))))
		return "";
	count = 0;
	memset(ret, 0, count + whites);
	while (*cmd){
		while (**cmd){
			ret[count] = **cmd;
			(*cmd)++;
			count++;
		}
		ret[count] = ' ';
		count++;
		cmd++;
	}
	return ret;
}

void c_msg(client_t* client, char **cmd, server_t *server)
{
	int cfd = -1;
	client_t *cli = NULL;
	char *msg = NULL;
	char *reply = NULL;

	if (!cmd[1]){
		s_send(client, ":server 411 :No recipient given (/msg)\r\n");
		return;
	}
	if ((cfd = get_client_fd(server->client, cmd[1])) == -1) {
		asprintf(&reply, "%s%s%s", ":server 401 ",
			 cmd[1], " :No such nick/channel\r\n");
		s_send(client, reply);
		return;
	} else {
		cli = get_client_by_fd(server->client, cfd);
		if (!cli)
			return;
		msg = reform(&cmd[2]);
		s_send(cli, client->name);
		s_send(cli, ": ");
		s_send(cli, msg);
		s_send(cli, "\n");
	}
}

void c_next_channel(client_t* client, char **cmd, server_t *server)
{
	unused(cmd);
	if ((server->channel)->next){
		(server->channel) = (server->channel)->next;
		s_send(client, "==> To the next channel we go\n");
	}
	else
		s_send(client, "there's no next channel\n");
}

void c_previous_channel(client_t* client, char **cmd, server_t *server)
{
	unused(cmd);
	if ((server->channel)->prev){
		(server->channel) = (server->channel)->prev;
		s_send(client, "==> To the previous channel we go\n");
	}
	else
		s_send(client, "there's no previous channel\n");
}

void s_diffuse(server_t *server, char *msg, int cfd)
{
	client_t *client = NULL;
	c_client_t *clients = NULL;
	channel_t *channel = NULL;
	msg_t *stored_msg = NULL;

	client = get_client_by_fd(server->client, cfd);
	if (client){
		channel = client->channel;
		clients = channel->clients;
		stored_msg = new_msg(client, msg);
		channel->msgs = l_add(stored_msg, channel->msgs);
		while (clients){
			if (clients->client->is_logged){
				s_send(clients->client, client->name);
				s_send(clients->client, ": ");
				s_send(clients->client, msg);
				s_send(clients->client, "\n");
			}
			clients = clients->next;
		}
	}
}
