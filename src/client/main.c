/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** main
*/

#include "client.h"

client_t client_inf;

int main(int ac, char **av)
{
	if (ac != 3) {
		printf("USAGE: ./client [ip] [port] \n");
		exit(1);
	}
	start_client(ac, av);
	return (0);
}
