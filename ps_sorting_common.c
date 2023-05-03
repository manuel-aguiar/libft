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

int find_exact_target(t_ps_stack *stack, int target)
{
	t_icpnode	*forward;
	t_icpnode	*backward;
	int			countpos;
	int			countneg;

	countpos = 0;
	countneg = 0;
	forward = stack->list->pivot;
	backward = stack->list->pivot;
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


int find_closest_in_bucket(t_ps_stack *stack, int min, int max)
{
	t_icpnode	*forward;
	t_icpnode	*backward;
	int			countpos;
	int			countneg;

	countpos = 0;
	countneg = 0;
	forward = stack->list->pivot;
	backward = stack->list->pivot;
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

void super_swap(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max)
{
	t_icpnode *a_cur;
	t_icpnode *b_cur;

	a_cur = a_stack->list->pivot;
	b_cur = b_stack->list->pivot;
	if (a_stack->list->len <= 1 || b_stack->list->len <= 1)
		return ;
	if (!in_bucket(a_cur->data, min, max) \
	|| !in_bucket(b_cur->data, min, max) \
	|| !in_bucket(a_cur->next->data, min, max) \
	|| !in_bucket(b_cur->next->data, min, max))
		return ;
	if (((a_cur->data == a_cur->next->data + 1 && a_stack->ascending) \
	|| (a_cur->data == a_cur->next->data - 1 && !a_stack->ascending)) \
	&& ((b_cur->data == b_cur->next->data + 1 && b_stack->ascending) \
	|| (b_cur->data == b_cur->next->data - 1 && !b_stack->ascending)))
	{
		pslist_swap_top(a_stack, 0);
		pslist_swap_top(b_stack, 0);
		ft_printf("ss\n");
	}
}
