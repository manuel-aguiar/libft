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

int is_sorted(t_ps_stack *a_stack, t_ps_stack *b_stack)
{
	t_icpnode *cur;

	if (a_stack->list->len == 1)
		return (1);
	cur = a_stack->list->pivot;
	if (cur->data != 0)
		return (0);
	cur = cur->next;
	while (cur != a_stack->list->pivot)
	{
		if ((cur->data != cur->prev->data + 1))
			return (0);
		cur = cur->next;
	}
	if (b_stack->list->len)
		return (0);
	return (1);
}
