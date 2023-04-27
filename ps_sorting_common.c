/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sorting_common.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:04:15 by marvin            #+#    #+#             */
/*   Updated: 2023/04/27 15:04:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int		in_bucket(int target, int min, int max)
{
    	return ((target >= min && target < max));
}

int		is_target(int target, int test)
{
	return (target == test);
}

int find_exact_target(t_icplist *list, int target)
{
	t_icpnode *forward;
	t_icpnode *backward;
	int countpos;
	int countneg;

	countpos = 0;
	countneg = 0;
	forward = list->pivot;
	backward = list->pivot;
	while (1)
	{
		if (!is_target(forward->data, target))
		{
			countpos++;
			forward = forward->next;
		}
		else
			break;
		if (!is_target(backward->data, target))
		{
			countneg--;
			backward = backward->prev;
		}
		else
			break;
	}
	if (is_target(forward->data, target))
		return (countpos);
	return (countneg);
}


int find_closest_in_bucket(t_icplist *list, int min, int max)
{
	t_icpnode *forward;
	t_icpnode *backward;
	int countpos;
	int countneg;

	countpos = 0;
	countneg = 0;
	forward = list->pivot;
	backward = list->pivot;
	while (1)
	{
		if (!in_bucket(forward->data, min, max))
		{
			countpos++;
			forward = forward->next;
		}
		else
			break;
		if (!in_bucket(forward->data, min, max))
		{
			countpos++;
			forward = forward->next;
		}
		else
			break;
		if (!in_bucket(backward->data, min, max))
		{
			countneg--;
			backward = backward->prev;
		}
		else
			break;
	}
	if (in_bucket(forward->data, min, max))
		return (countpos);
	return (countneg);
}

void super_swap(t_icplist *alist, t_icplist *blist, int min, int max)
{
	if (alist->len <= 1 || blist->len <= 1)
		return ;
	if (!in_bucket(alist->pivot->data, min, max) \
	|| !in_bucket(blist->pivot->data, min, max) \
	|| !in_bucket(alist->pivot->next->data, min, max) \
	|| !in_bucket(blist->pivot->next->data, min, max))
		return ;
	if (alist->pivot->data == alist->pivot->next->data + 1\
	&& blist->pivot->data == blist->pivot->next->data - 1)
	{
		pslist_swap_top(alist, NULL);
		pslist_swap_top(blist, NULL);
		ft_printf("ss\n");
		//counter++;
		//ss_counter++;
	}
}
