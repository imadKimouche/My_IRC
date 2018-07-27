/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** tools source file
*/

#include <irc.h>


int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_number(char *num)
{
	int i = 0;

	while (num[i] != '\0'){
		if (!is_digit(num[i])){
			fprintf(stderr, "invalid argument, please enter a port number\n");
			return (0);
		}
		i++;
	}
	return (1);
}

char *add_str(char **str1, char *str2)
{
	int size1 = 0;
	int size2 = 0;

	if (*str1)
		size1 = strlen(*str1);
	if (str2)
		size2 = strlen(str2);
	*str1 = realloc(*str1, sizeof(char) * (size1 + size2 + 1));
	strcat(*str1, str2);
	(*str1)[size1 + size2] = '\0';
	return (*str1);
}

char **split(char *line, char *delimiters)
{
	char *tok = NULL;
	char **res = NULL;
	int nb = 0;

	tok = strtok(strdup(line), delimiters);
	while (tok != NULL) {
		res = realloc(res, sizeof(char *) * (++nb));
		res[nb - 1] = calloc(sizeof(char), strlen(tok));
		res[nb - 1] = tok;
		tok = strtok(NULL, delimiters);
	}
	res = realloc(res, sizeof(char *) * (++nb));
	res[nb - 1] = NULL;
	return (res);
}

/*void display(client_t *client, char **cmd, server_t *server)
{
	printf("Client:\n");
	while (client) {
		printf("\t%d is logged : %d\n", client->fd, client->is_logged);
		client = client->next;
	}
	printf("Cmd:\n");
	while (*cmd) {
		printf("\t%s\n", *cmd);
		cmd++;
	}
	printf("Server:\n");
	channel_t *ch = server->channel;
	while (ch) {
		printf("\t%s\n", ch->c_name);
		ch = ch->next;
	}
}*/
char *trim(char *str)
{
	char *ret = NULL;
	int whites = 0;
	int i = 0;

	while (str[i]) {
		if (str[i] == '\r' || str[i] == '\n')
			whites++;
		i++;
	}
	whites = strlen(str) - whites;
	if (!(ret = malloc((len(char) * whites) + 1)))
		return (str);
	strncpy(ret, str, whites);
	return (ret);
}
