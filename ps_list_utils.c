/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_arr_to_cdlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:41 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 10:46:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ps_arr_to_cdlist(t_icplist **list, int **arr, int size)
{
	t_icplist *new;
	int i;
	int *array;

	new = icplist_new(size, NULL);
	if (new)
	{
		array = *arr;
		i = -1;
		while (++i < size)
			icplist_in_tail(new, array[i]);
	}
	*list = new;
	free(array);
	*arr = NULL;
	if (new)
		return (1);
	return (malloc_failed());
}

void	ps_printlists(t_icplist *a_list, t_icplist *b_list, void (*pnt)(int))
{
	ft_printf("\nlist B: ");
	icplist_head_print(b_list, pnt);
	ft_printf("\n\nlist A: ");
	icplist_head_print(a_list, pnt);
	ft_printf("\n\n");
}

void	printmembs(int num)
{
	ft_printf("%d   ", num);
}

int is_sorted(t_icplist *alist, t_icplist *blist)
{
	t_icpnode *cur;

	if (alist->len == 1)
		return (1);
	cur = alist->pivot;
	if (cur->data != 0)
		return (0);
	cur = cur->next;
	while (cur != alist->pivot)
	{
		if ((cur->data != cur->prev->data + 1))
			return (0);
		cur = cur->next;
	}
	if (blist->len)
		return (0);
	return (1);
}
