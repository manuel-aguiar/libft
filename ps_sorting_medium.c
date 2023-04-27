/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_sorting_medium.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:41:11 by marvin            #+#    #+#             */
/*   Updated: 2023/04/27 16:41:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void quick_medium_b(t_icplist *alist, t_icplist *blist, int start, int end)
{
	int mid;

	mid = (start + end) / 2;
	if (end - start < 2)
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

void quick_medium_a(t_icplist *alist, t_icplist *blist, int start, int end)
{
	int mid;

	mid = (start + end) / 2;

	if (end - start < 2)
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
