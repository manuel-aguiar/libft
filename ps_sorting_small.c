/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sorting_small.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:04:40 by marvin            #+#    #+#             */
/*   Updated: 2023/04/27 16:04:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/* HARDCODED TROLOLOLOL*/
/*
void 	pushswap_sort_two(t_icplist *list, int ascending, char *print)
{
	if ((list->pivot->data > list->pivot->next->data && ascending) \
	|| (list->pivot->data < list->pivot->next->data && !ascending))
	{
		pslist_swap_top(list, NULL);
		if (print)
			ft_printf("%s\n", print);
	}
}

void	pushswap_sort_three(t_icplist *list)
{
	t_icpnode *cur;

	cur = list->pivot;
	if (cur->data < cur->next->data)
	{

	}

	if (cur->data < cur)
	{
		pslist_rotate(list, -1, "rra");
		pslist_swap_top(list, "sa");
	}
	if (cur->data == 1)
	{
		if (cur->next->data == 0)
			pslist_swap_top(list, "sa");
		else
			pslist_rotate(list, -1, "rra");
	}
	if (cur->data > cur->next->data && cur->data > cur->prev->data)
	{
		if (cur->next->data > cur->prev->data)
		{
			pslist_swap_top(list, "sa");
			pslist_rotate(list, -1, "rra");
		}
		else
			pslist_rotate(list, 1, "ra");
	}
}

void	pushswap_sort_small(t_icplist *alist, t_icplist *blist, int min, int max)
{
	pushbucket_from_a(alist, blist, min, max / 2);
	if (blist->len == 2);
}*/
