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

void quick_sort_b(t_icplist *alist, t_icplist *blist, int start, int end)
{
	int mid;

	mid = (start + end) / 2;
	if (end - start < INSORT_TO_A)
	{
		//printf("calling INSERTION SORT to A to finish, start %d, mid %d, counter %d\n", start, end, counter);
		//ps_printlists(alist, blist, &printmembs);
		insertion_sort_from_b(alist, blist, start, end);
		//ps_printlists(alist, blist, &printmembs);
		return ;
	}
	//printf("pushing to A, mid %d, end %d, counter %d\n", mid, end, counter);
	pushbucket_from_b(alist, blist, mid, end);

	//ps_printlists(alist, blist, &printmembs);

	//printf("calling quicksort A, sending inputs mid %d, end %d\n", mid, end);
	quick_sort_a(alist, blist, mid, end);

	//printf("calling quicksort B recursively, sending inputs mid %d, end %d\n", start, mid);
	quick_sort_b(alist, blist, start, mid);

}

void quick_sort_a(t_icplist *alist, t_icplist *blist, int start, int end)
{
	int mid;

	mid = (start + end) / 2;

	if (end - start < INSORT_TO_B)
	{
		//printf("calling INSERTION SORT to B to finish, start %d, mid %d, counter %d\n", start, end, counter);
		//ps_printlists(alist, blist, &printmembs);
		insertion_sort_from_a(blist, alist, start, end);
		pushbucket_from_b(alist, blist, start, end);
		//ps_printlists(alist, blist, &printmembs);
		return ;
	}
	//printf("pushing to B, start %d, mid %d, counter %d\n", start, mid, counter);
	pushbucket_from_a(alist, blist, start, mid);
	//ps_printlists(alist, blist, &printmembs);

	//printf("calling quicksort A recursively to sort the second half, sending inputs start %d, mid %d\n", mid, end);
	quick_sort_a(alist, blist, mid, end);
	//printf("calling quicksort B, sending inputs start %d, mid %d\n", start, mid);
	quick_sort_b(alist, blist, start, mid);

}


void pushswap(t_icplist *alist, t_icplist *blist, int total)
{
	quick_sort_a(alist, blist, 0, total);
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
