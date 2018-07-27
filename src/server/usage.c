/*
** EPITECH PROJECT, 2018
** My ftp
** File description:
** help / usage
*/

#include "irc.h"

void usage(char *str)
{
	if (!str || (str && !(strcmp(str, "-help"))))
		fprintf(stderr, "USAGE: ./server port\n");
	exit(0);
}
