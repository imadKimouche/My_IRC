/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** client cmd 2
*/

#include "irc.h"

int valid_nick(client_t *clients, char *cmd)
{
	while (clients){
		if (!strcmp(cmd, clients->name))
			return (0);
		clients = clients->next;
	}
	return (1);
}

char* pick_random(const char *filename)
{
	FILE *f;
	size_t lineno = 0;
	size_t selectlen;
	char selected[512];
	char current[512];

	selected[0] = '\0';
	f = fopen(filename, "r");
	while (fgets(current, sizeof(current), f)) {
		if (drand48() < 1.0 / ++lineno) {
			strcpy(selected, current);
		}
	}
	fclose(f);
	selectlen = strlen(selected);
	if (selectlen > 0 && selected[selectlen-1] == '\n') {
		selected[selectlen-1] = '\r';
		selected[selectlen-1] = '\n';
	}
	return strdup(selected);
}

int check_client(client_t *client, char *cmd_user, char *name)
{
	char *quote = NULL;
	char reply[256];

	if (cmd_user){
		client->username = strdup(cmd_user);
		client->is_registered = 1;
		quote = pick_random("./data/quote.txt");
		memset(reply, 0, 256);
		sprintf(reply, "%s%s%s\r\n", ":server 001 ", name,
			" :Welcome on my_irc, you're on #ALL");
		s_send(client, reply);
		s_send(client, ":server 002 :*** Quote of the day ***\r\n");
		s_send(client, ":server 003 : ");
		s_send(client, quote);
	}
	else {
		s_send(client, ":server 461 /user :Not enough parameters\r\n");
		return (0);
	}
	return (1);
}

int register_client(client_t *client, char* name)
{
	char *username = NULL;
	char **cmd_user = NULL;

	if (!client->is_registered){
		username = s_receive(client);
		if (!(cmd_user = split(username, " ")))
			return (0);
		if (!strcmp(cmd_user[0], "/user")
		    && !check_client(client, cmd_user[1], name))
			return (0);
		else if (strcmp(cmd_user[0], "/user")){
			s_send(client, ":server 421 :Unknown command\r\n");
			return (0);
		}
	}
	return (1);
}
