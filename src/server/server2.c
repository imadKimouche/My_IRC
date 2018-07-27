/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** server2
*/

#include "irc.h"

void accept_and_receive(server_t *s, int *i)
{
        client_t *new = NULL;
	channel_t *channel = NULL;

        if (FD_ISSET(*i, &s->rfds) && *i == s->fd){
	        s->cfd = s_accept(s);
		if (s->cfd == -1)
			return;
		channel = get_channel_from_name("#ALL", s->channel);
		s->max_fd = (s->max_fd < s->cfd ? s->cfd : s->max_fd);
		new = new_client(s->cfd, channel);
		c_client_t *c = new_channel_client(new);
		channel->clients = l_add(c, channel->clients);
		s->client = l_add(new, s->client);
		printf("NEW CLIENT\n");
        }
	else if (FD_ISSET(*i, &s->rfds)) {
		new = get_client_by_fd(s->client, *i);
		s_run_cmd(s, s_receive(new), *i);
	}
}

void run(server_t *server, client_t *client, char **ret, char *com, int fd)
{
	int bool = 0;

	for (int i = 0; i < 9; i++){
	        if (!strcmp(cmd[i].command, ret[0])){
			if (client->is_registered)
				cmd[i].fct(client, ret, server);
			else if (!strcmp(cmd[i].command, "/nick"))
				cmd[i].fct(client, ret, server);
			else
				s_send(client, ":server 451 :You have not registered\r\n");
			bool = 1;
		}
	}
	if (!bool){
		if (client->is_registered)
			s_diffuse(server, com, fd);
		else
			s_send(client, ":server 451 :You have not registered\r\n");
	}
}

void s_run_cmd(server_t *s, char *com, int fd)
{
	char **ret = NULL;
	client_t *client = NULL;

	client = get_client_by_fd(s->client, fd);
	if (!client)
		return;
	if (!com){
		client->is_logged = 0;
		close(fd);
		FD_CLR(fd, &s->rfds);
		return;
	}
	com = trim(com);
	ret = split(com, " ");
	if (!ret[0])
		return;
        run(s, client, ret, com, fd);
}
