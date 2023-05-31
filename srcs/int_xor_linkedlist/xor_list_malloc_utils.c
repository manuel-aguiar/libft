/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_list_malloc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:58:48 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 14:58:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_xor_list.h"

static t_ixmnode	*xor_func(t_ixmnode *prev, t_ixmnode *next)
{
	return ((t_ixmnode*)((uintptr_t)prev ^ (uintptr_t)next));
}

void	ixmlist_del_head(t_ixmlist *list)
{
	t_ixmnode	*cur;
	t_ixmnode	*next;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	next = xor_func(cur->xor_ptr, NULL);
	if (next)
		next->xor_ptr = xor_func(cur, next->xor_ptr);
	else
		list->tail = NULL;
	list->head = next;
	free(cur);
	--(list->len);
}

void	ixmlist_del_tail(t_ixmlist *list)
{
	t_ixmnode	*cur;
	t_ixmnode	*prev;

	if (!list || !(list->tail))
		return ;
	cur = list->tail;
	prev = xor_func(cur->xor_ptr, NULL);
	if (prev)
		prev->xor_ptr = xor_func(prev->xor_ptr, cur);
	else
		list->head = NULL;
	list->tail = prev;
	free(cur);
	--(list->len);
}

void	ixmlist_head_print(t_ixmlist *list, void (*pnt)(int))
{
	t_ixmnode	*cur;
	t_ixmnode	*prev;
	t_ixmnode	*next;

	if (!list)
		return ;
	cur = list->head;
	prev = NULL;
	while (cur)
	{
		pnt(cur->data);
		next = xor_func(prev, cur->xor_ptr);
		prev = cur;
		cur = next;
	}
}

void	ixmlist_tail_print(t_ixmlist *list, void (*pnt)(int))
{
	t_ixmnode	*cur;
	t_ixmnode	*prev;
	t_ixmnode	*next;

	if (!list)
		return ;
	cur = list->tail;
	next = NULL;
	while (cur)
	{
		pnt(cur->data);
		prev = xor_func(next, cur->xor_ptr);
		next = cur;
		cur = prev;
	}
}

void	ixmlist_destroy(t_ixmlist **list)
{
	if (!list || !*list)
		return ;
	while ((*list)->head)
		ixmlist_del_head(*list);
	ft_free_set_null(list);
}
