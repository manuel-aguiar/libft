/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sorting_a_stack.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:14:26 by marvin            #+#    #+#             */
/*   Updated: 2023/04/27 15:14:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void 	swap_on_pushing_from_a(t_icplist *alist, int min, int max)
{
	if (alist->pivot->data == alist->pivot->next->data + 1 \
	&& !in_bucket(alist->pivot->data, min, max) \
	&& !in_bucket(alist->pivot->next->data, min, max))
	{
		pslist_swap_top(alist, "sa");
		sa_counter++;
	}
}

void pushbucket_from_a(t_icplist *alist, t_icplist *blist, int min, int max)
{
    int size;
	int closest;
    size = max - min;

    while (size--)
    {
		closest = find_closest_in_bucket(alist, min, max);
		if (closest < 0)
		{
			while (closest++ < 0)
			{
				swap_on_pushing_from_a(alist, min, max);
				pslist_rotate(alist, -1, "rra");
				counter++;

			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				swap_on_pushing_from_a(alist, min, max);
				pslist_rotate(alist, 1, "ra");
				counter++;

			}
		}
		super_swap(alist, blist, min, max);
        pslist_push_top(blist, alist, "pb");
        counter++;
    }
}

static void 	swap_on_insertion_from_a(t_icplist *alist, int target, int min, int max)
{
	if (alist->len <= 1)
		return ;
	if (alist->pivot->data == alist->pivot->next->data + 1 \
	&& !is_target(alist->pivot->data, target) \
	&& !is_target(alist->pivot->next->data, target) \
	&& in_bucket(alist->pivot->data, min, max) \
	&& in_bucket(alist->pivot->next->data, min, max))
	{
		pslist_swap_top(alist, "sa");
		sa_counter++;
	}
}

static void 	put_target_to_top_a(t_icplist *alist, int target, int min, int max)
{
	int i;

	i = find_exact_target(alist, target);
    if (i > 0)
    {
        while (i--)
        {
            pslist_rotate(alist, 1, "ra");
            counter++;
			swap_on_insertion_from_a(alist, target, min, max);
        }
    }
    else
    {
        while (i++)
        {
            pslist_rotate(alist, -1, "rra");
            counter++;
			swap_on_insertion_from_a(alist, target, min, max);
        }
    }
}

void insertion_sort_from_a(t_icplist *to, t_icplist *from, int start, int end)
{
	int size;

	size = end - start;
	while (size--)
	{
		put_target_to_top_a(from, start++, start, end);
		pslist_push_top(to, from, "pb");
		counter++;
	}
}
