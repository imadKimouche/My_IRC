/*
** EPITECH PROJECT, 2018
** My ftp
** File description:
** list editing
*/

#include "irc.h"

void *l_add(void *elem, void *list)
{
	list_t *elem_l = (list_t *)elem;
	list_t *list_l = (list_t *)list;

	if (list == NULL)
		return elem;
	else if (elem == NULL)
		return list;
	list_l->prev = elem_l;
	elem_l->next = list_l;
	return (elem_l);
}

void l_remove(void **list, int index)
{
	list_t *elem_l = (list_t *)*list;

	for (int i = 0; i < index; i++) {
		if (elem_l == NULL)
			return;
		elem_l = elem_l->next;
	}
	if (elem_l == NULL)
		return;
	if (elem_l->prev == NULL) {
		*list = elem_l->next;
		if (elem_l->next)
			elem_l->next->prev = NULL;
	} else {
		elem_l->prev->next = elem_l->next;
		if (elem_l->next != NULL)
			elem_l->next->prev = elem_l->prev;
	}
}

void l_clean(void **elem)
{
	list_t *elem_l = (list_t *) *elem;
	list_t *toDelete = NULL;

	while (elem_l) {
		toDelete = elem_l;
		elem_l = elem_l->next;
		free(toDelete);
	}
	*elem = NULL;
}
