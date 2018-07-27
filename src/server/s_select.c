/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** s_select source file
*/

#include "irc.h"

void set_time(xtime *tv)
{
	tv->tv_sec = TIMEOUT;
	tv->tv_usec = 0;
}

int s_select(server_t *s)
{
	int ret = -1;
	xtime tv;
	set_time(&tv);
	ret = select(s->max_fd + 1, &s->rfds, NULL, NULL, &tv);
	if (ret == -1){
		error_handle("select");
		return (-1);
	}
	else if (!ret)
		return (-1);
	return (1);
}
