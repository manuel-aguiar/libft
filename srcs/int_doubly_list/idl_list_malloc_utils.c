/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_list_malloc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:01 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:45:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_dl_list.h"

int	idmlist_find(t_idmlist *list, int target)
{
	t_idmnode	*cur;

	if (!list || !(list->head))
		return (0);
	cur = list->head;
	while (cur)
	{
		if (cur->data == target)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	idmlist_remove_if(t_idmlist *list, int target)
{
	t_idmnode	*cur;
	t_idmnode	*next;

	if (!list || !list->head)
		return ;
	cur = list->head;
	while (cur)
	{
		next = cur->next;
		if (cur->data == target)
		{
			if (cur->prev)
				cur->prev->next = cur->next;
			else
			{
				list->head = cur->next;
				cur->next->prev = NULL;
			}
			if (cur->next)
				cur->next->prev = cur->prev;
			else
			{
				list->tail = cur->prev;
				cur->prev->next = NULL;
			}
			free(cur);
		--(list->len);
		}
		cur = next;
	}
}

void	idmlist_del_head(t_idmlist *list)
{
	t_idmnode	*cur;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	if (cur->next)
		cur->next->prev = NULL;
	else
		list->tail = NULL;
	list->head = cur->next;
	free(cur);
	--(list->len);
}

void	idmlist_del_tail(t_idmlist *list)
{
	t_idmnode	*cur;

	if (!list || !(list->tail))
		return ;
	cur = list->tail;
	if (cur->prev)
		cur->prev->next = NULL;
	else
		list->head = NULL;
	list->tail = cur->prev;
	free(cur);
	--(list->len);
}

void	idmlist_head_print(t_idmlist *list, void (*pnt)(int))
{
	t_idmnode	*cur;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->next;
	}
}

void	idmlist_tail_print(t_idmlist *list, void (*pnt)(int))
{
	t_idmnode	*cur;

	if (!list)
		return ;
	cur = list->tail;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->prev;
	}
}

void	idmlist_destroy(t_idmlist **list)
{
	t_idmnode	*del;
	t_idmnode	*next;

	if (!list || !*list)
		return ;
	del = (*list)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
	ft_free_set_null(list);
}
