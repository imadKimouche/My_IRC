/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** client
*/

#include "client.h"

void *c_input_handle(void *arg)
{
	client_t *client = (client_t *)arg;
	char *buff = calloc(sizeof(char), 1000);

	while (client_inf.state != 1) {
		buff = c_receive();
		if (buff)
			handle_output_cmd(buff, client);
	}
	free(buff);
	pthread_exit(0);
}

void c_start_input_captation(client_t *client)
{
	pthread_t *thread = malloc(sizeof(pthread_t));

	pthread_create(thread, NULL, c_input_handle, client);
}

void start_client(int ac, char **av)
{
	client_inf.state = 0;
	c_connect(atoi(av[2]), av[1]);
	start_gui(ac, av);
}
