/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** main
*/

#include "irc.h"

int main(int ac, char **av)
{
	server_t *s = NULL;

	if (ac != 2){
		usage(av[1]);
		return (0);
	}
	s_init(av[1], &s);
	s_run(&s);
	return (0);
}
