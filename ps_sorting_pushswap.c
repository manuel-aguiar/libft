/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sorting_pushswap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:11:41 by marvin            #+#    #+#             */
/*   Updated: 2023/04/27 15:11:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void quick_sort_b(t_ps_stack *a_stack, t_ps_stack *b_stack, int start, int end)
{
	int mid;

	if (end - start < INSORT_TO_A || bucket_is_sorted(b_stack, start, end, 0))
	{
		insertion_sort_push(a_stack, b_stack, start, end);
		return ;
	}
	mid = (start + end) / 2;
	//printf("pushing to A, mid %d, end %d, counter %d\n", mid, end, counter);
	pushbucket(b_stack, a_stack, mid, end);

	//ps_printlists(alist, blist, &printmembs);

	//printf("calling quicksort A, sending inputs mid %d, end %d\n", mid, end);
	quick_sort_a(a_stack, b_stack, mid, end);

	//printf("calling quicksort B recursively, sending inputs mid %d, end %d\n", start, mid);
	quick_sort_b(a_stack, b_stack, start, mid);

}

void quick_sort_a(t_ps_stack *a_stack, t_ps_stack *b_stack, int start, int end)
{
	int mid;

	if (bucket_is_sorted(a_stack, start, end, 1))
		return ;
	mid = (start + end) / 2;
	if (end - start < INSORT_TO_B)
	{
		//printf("calling INSERTION SORT to B to finish, start %d, mid %d, counter %d\n", start, end, counter);
		//ps_printlists(alist, blist, &printmembs);
		//insertion_sort_push(b_stack, a_stack, start, end);
		//pushbucket(b_stack, a_stack, start, end);
		//printf("using cocktail on a, from %d to %d\n", start, end);
		//ps_printlists(a_stack->list, b_stack->list, &printmembs);
		//stack_cocktail(a_stack, start, end, O_PRINT | O_COUNT);
		pushswap_super_small(a_stack, b_stack, start, end);
		//printf("after cocktail on a, from %d to %d\n", start, end);
		//ps_printlists(a_stack->list, b_stack->list, &printmembs);
		//ps_printlists(alist, blist, &printmembs);
		return ;
	}
	//printf("pushing to B, start %d, mid %d, counter %d\n", start, mid, counter);
	pushbucket(a_stack, b_stack, start, mid);
	//ps_printlists(alist, blist, &printmembs);

	//printf("calling quicksort A recursively to sort the second half, sending inputs start %d, mid %d\n", mid, end);
	quick_sort_a(a_stack, b_stack, mid, end);
	//printf("calling quicksort B, sending inputs start %d, mid %d\n", start, mid);
	quick_sort_b(a_stack, b_stack, start, mid);

}


void pushswap(t_ps_stack *a_stack, t_ps_stack *b_stack, int total)
{
	t_icplist *alist;
	t_icplist *blist;

	alist = a_stack->list;
	blist = b_stack->list;

	if (total <= 2)
		pushswap_sort_two(a_stack, 1);
	else if (total <= 10)
		stack_cocktail(a_stack, 0, total, O_PRINT | O_COUNT);
	/*else if (total <= 18)
	{
		insertion_sort_push(b_stack, a_stack, 0, total);
		insertion_sort_push(a_stack, b_stack, 0, total);
	}*/

	else
		quick_sort_a(a_stack, b_stack, 0, total);
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
	/*
	if (total == 2)
		pslist_swap_top(alist, "sa");
	else if (total == 3)
		pushswap_sort_three(alist);
	else if (total <= 6)
		pushswap_sort_small(alist, blist, 0, total);
	else
		quick_sort_a(alist, blist, 0, total);*/
}
