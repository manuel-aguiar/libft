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


int	stack_sort_len(t_ps_stack *stack, int len, int front)
{
	int i;
	t_icpnode *cur;

	if (front)
		cur = stack->list->pivot;
	else
		cur = stack->list->pivot->prev;
	i = 0;
	while (i++ < len)
	{
		if ((cur->data != cur->next->data - 1  && stack->ascending)\
		|| (cur->data != cur->next->data + 1 && !stack->ascending))
			return (0);
		if (front)
			cur = cur->next;
		else
			cur = cur->prev;
	}
	return (1);
}


void	stack_cocktail(t_ps_stack *stack, int print)
{
	t_icpnode	*cur;
	int			i;
	int			len;
	int			stop;

	cur = stack->list->pivot;
	len = stack->list->len;
	i = 0;
	while (!stack_sort_len(stack, len - i - 1, 1))
	{
		pushswap_sort_two(stack, print);
		while (i < len - 2  && !stack_sort_len(stack, len - i - 1, 1))
		{
			pslist_rotate(stack, 1, 1);
				i++;
			pushswap_sort_two(stack, print);
		}
		while (i > 0 && !stack_sort_len(stack, i, 0))
		{
			pslist_rotate(stack, -1, 1);
				i--;
			pushswap_sort_two(stack, print);
		}
	}
	while (i-- > 0)
		pslist_rotate(stack, -1, 1);
}


void 	pushswap_sort_two(t_ps_stack *stack, int print)
{
	t_icpnode *cur;

	cur = stack->list->pivot;
	if ((cur->data > cur->next->data && stack->ascending) \
	|| (cur->data < cur->next->data && !stack->ascending))
		pslist_swap_top(stack, 1);
}

void 	pushswap_sort_three(t_ps_stack *stack)
{
	if (stack->list->pivot->data > stack->list->pivot->next->data)
	{
		if (stack->list->pivot->data > stack->list->pivot->prev->data)
		{
			if (stack->list->pivot->next->data > stack->list->pivot->prev->data)
			{
				pslist_swap_top(stack, 1);
				pslist_rotate(stack, -1, 1);
			}
			else
				pslist_rotate(stack, 1, 1);
		}
		else
			pslist_rotate(stack, 1, 1);
	}
	else
	{
		pslist_rotate(stack, -1, 1);
		if (stack->list->pivot->data < stack->list->pivot->prev->data)
			pslist_swap_top(stack, 1);
	}
}


void pushswap_super_small(t_ps_stack *a_stack, t_ps_stack *b_stack)
{
	int len;

	len = a_stack->list->len;
	pushbucket(a_stack, b_stack, 0, len / 2);
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
	if (a_stack->list->len == 2)
		pushswap_sort_two(a_stack, 1);
	else
		stack_cocktail(a_stack, 1);
	if (b_stack->list->len == 2)
		pushswap_sort_two(b_stack, 1);
	else
		stack_cocktail(b_stack, 1);
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
	insertion_sort_push(a_stack, b_stack, 0, len / 2);
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
}


/*
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
