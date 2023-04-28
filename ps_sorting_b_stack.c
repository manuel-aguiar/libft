/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_buckets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:29:36 by marvin            #+#    #+#             */
/*   Updated: 2023/04/25 10:29:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"


/*reverse rotation is twice as costly as positive, positive already
moves the array forward, 20 savings on 100, 100 savings on 500
1000 savings on 5000*/

static void 	swap_on_pushing_from_b(t_icplist *blist, int min, int max)
{
	if (blist->pivot->data == blist->pivot->next->data - 1 \
	&& !in_bucket(blist->pivot->data, min, max) \
	&& !in_bucket(blist->pivot->next->data, min, max))
	{
		pslist_swap_top(blist, "sb");
		sb_counter++;
	}
}

void pushbucket_from_b(t_icplist *alist, t_icplist *blist, int min, int max)
{
    int size;
	int closest;
    size = max - min;

    while (size--)
    {
		closest = find_closest_in_bucket(blist, min, max);
		if (closest < 0)
		{
			while (closest++ < 0)
			{
				swap_on_pushing_from_b(blist, min, max);
				pslist_rotate(blist, -1, "rrb");
				counter++;

			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				swap_on_pushing_from_b(blist, min, max);
				pslist_rotate(blist, 1, "rb");
				counter++;

			}
		}
		super_swap(alist, blist, min, max);
        pslist_push_top(alist, blist, "pa");
		counter++;
	}
}

/* in insertion sort you ahve a specific target
always try to get there asap */

static void 	swap_on_insertion_from_b(t_icplist *blist, int target, int min, int max)
{
	if (blist->len <= 1)
		return ;
	if (blist->pivot->data == blist->pivot->next->data - 1 \
	&& !is_target(blist->pivot->data, target) \
	&& !is_target(blist->pivot->next->data, target) \
	&& in_bucket(blist->pivot->data, min, max) \
	&& in_bucket(blist->pivot->next->data, min, max))
	{
		pslist_swap_top(blist, "sb");
		sb_counter++;
	}
}

static void 	put_target_to_top_b(t_icplist *blist, int target, int min, int max)
{
	int i;

	i = find_exact_target(blist, target);
    if (i > 0)
    {
        while (i--)
        {
			pslist_rotate(blist, 1, "rb");
            counter++;
			swap_on_insertion_from_b(blist, target, min, max);
        }
    }
    else
    {
        while (i++)
        {
			pslist_rotate(blist, -1, "rrb");
            counter++;
			swap_on_insertion_from_b(blist, target, min, max);
        }
    }
}

void	insertion_sort_from_b(t_icplist *to, t_icplist *from, int start, int end)
{
	int size;

	size = end - start;
	while (size--)
	{
		put_target_to_top_b(from, --end, start, end);
		pslist_push_top(to, from, "pa");
		counter++;
	}
}

