/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** actions
*/

#include "client.h"

void a_send(GtkWidget *widget, gpointer data)
{
	unused(widget);
	unused(data);
	handle_input_cmd();
}
