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

static int counter;
static int ss_counter;
static int sa_counter;
static int sb_counter;

int     in_bucket(int target, int min, int max)
{
    	return ((target >= min && target < max));
}

int is_target(int target, int test)
{
	return (target == test);
}

int find_exact_target(t_icplist *list, int target);

int find_closest_in_bucket(t_icplist *list, int min, int max);

void 	swap_on_insertion_from_a(t_icplist *alist, int target, int min, int max)
{
	if (alist->len <= 1)
		return ;
	if (alist->pivot->data == alist->pivot->next->data + 1 \
	&& !is_target(alist->pivot->data, target) \
	&& !is_target(alist->pivot->next->data, target) \
	&& in_bucket(alist->pivot->data, min, max) \
	&& in_bucket(alist->pivot->next->data, min, max))
	{
		icplist_swap_top(alist, "sa");
		sa_counter++;
	}
}

void 	put_target_to_top_a(t_icplist *alist, int target, int min, int max)
{
	int i;

	i = find_exact_target(alist, target);
    if (i > 0)
    {
        while (i--)
        {
            icplist_rotate(alist, 1, "ra");
            counter++;
			swap_on_insertion_from_a(alist, target, min, max);
        }
    }
    else
    {
        while (i++)
        {
            icplist_rotate(alist, -1, "rra");
            counter++;
			swap_on_insertion_from_a(alist, target, min, max);
        }
    }
}

void 	swap_on_insertion_from_b(t_icplist *blist, int target, int min, int max)
{
	if (blist->len <= 1)
		return ;
	if (blist->pivot->data == blist->pivot->next->data - 1 \
	&& !is_target(blist->pivot->data, target) \
	&& !is_target(blist->pivot->next->data, target) \
	&& in_bucket(blist->pivot->data, min, max) \
	&& in_bucket(blist->pivot->next->data, min, max))
	{
		icplist_swap_top(blist, "sb");
		sb_counter++;
	}
}

void 	put_target_to_top_b(t_icplist *blist, int target, int min, int max)
{
	int i;

	i = find_exact_target(blist, target);
    if (i > 0)
    {
        while (i--)
        {
			icplist_rotate(blist, 1, "rb");
            counter++;
			swap_on_insertion_from_b(blist, target, min, max);
        }
    }
    else
    {
        while (i++)
        {
			icplist_rotate(blist, -1, "rrb");
            counter++;
			swap_on_insertion_from_b(blist, target, min, max);
        }
    }
}


/*reverse rotation is twice as costly as positive, positive already
moves the array forward, 20 savings on 100, 100 savings on 500
1000 savings on 5000*/


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
		icplist_swap_top(alist, NULL);
		icplist_swap_top(blist, NULL);
		ft_printf("ss\n");
		counter++;
		ss_counter++;
	}
}

void 	swap_on_pushing_from_a(t_icplist *alist, int min, int max)
{
	if (alist->pivot->data == alist->pivot->next->data + 1 \
	&& !in_bucket(alist->pivot->data, min, max) \
	&& !in_bucket(alist->pivot->next->data, min, max))
	{
		icplist_swap_top(alist, "sa");
		sa_counter++;
	}
}

void pushbucket_to_b(t_icplist *alist, t_icplist *blist, int min, int max)
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
				icplist_rotate(alist, -1, "rra");
				counter++;

			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				swap_on_pushing_from_a(alist, min, max);
				icplist_rotate(alist, 1, "ra");
				counter++;

			}
		}
		super_swap(alist, blist, min, max);
        icplist_push_top(blist, alist, "pb");
        counter++;
    }
}


void 	swap_on_pushing_from_b(t_icplist *blist, int min, int max)
{
	if (blist->pivot->data == blist->pivot->next->data - 1 \
	&& !in_bucket(blist->pivot->data, min, max) \
	&& !in_bucket(blist->pivot->next->data, min, max))
	{
		icplist_swap_top(blist, "sb");
		sb_counter++;
	}
}

void pushbucket_to_a(t_icplist *alist, t_icplist *blist, int min, int max)
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
				icplist_rotate(blist, -1, "rrb");
				counter++;

			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				swap_on_pushing_from_b(blist, min, max);
				icplist_rotate(blist, 1, "rb");
				counter++;

			}
		}
		super_swap(alist, blist, min, max);
        icplist_push_top(alist, blist, "pa");
		counter++;
	}
}

/* in insertion sort you ahve a specific target
always try to get there asap */

void insertion_sort_to_b(t_icplist *to, t_icplist *from, int start, int end)
{
	int size;

	size = end - start;
	while (size--)
	{
		put_target_to_top_a(from, start++, start, end);
		icplist_push_top(to, from, "pb");
		counter++;
	}
}

void	insertion_sort_to_a(t_icplist *to, t_icplist *from, int start, int end)
{
	int size;

	size = end - start;
	while (size--)
	{
		put_target_to_top_b(from, --end, start, end);
		icplist_push_top(to, from, "pa");
		counter++;
	}
}



void quick_sort_a(t_icplist *alist, t_icplist *blist, int start, int end);
void quick_sort_b(t_icplist *alist, t_icplist *blist, int start, int end);

void quick_sort_b(t_icplist *alist, t_icplist *blist, int start, int end)
{
	int mid;

	mid = (start + end) / 2;
	if (end - start < INSORT_TO_A)
	{
		//printf("calling INSERTION SORT to A to finish, start %d, mid %d, counter %d\n", start, end, counter);
		//ps_printlists(alist, blist, &printmembs);
		insertion_sort_to_a(alist, blist, start, end);
		//ps_printlists(alist, blist, &printmembs);
		return ;
	}
	//printf("pushing to A, mid %d, end %d, counter %d\n", mid, end, counter);
	pushbucket_to_a(alist, blist, mid, end);

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
		insertion_sort_to_b(blist, alist, start, end);
		pushbucket_to_a(alist, blist, start, end);
		//ps_printlists(alist, blist, &printmembs);
		return ;
	}
	//printf("pushing to B, start %d, mid %d, counter %d\n", start, mid, counter);
	pushbucket_to_b(alist, blist, start, mid);
	//ps_printlists(alist, blist, &printmembs);

	//printf("calling quicksort A recursively to sort the second half, sending inputs start %d, mid %d\n", mid, end);
	quick_sort_a(alist, blist, mid, end);
	//printf("calling quicksort B, sending inputs start %d, mid %d\n", start, mid);
	quick_sort_b(alist, blist, start, mid);

}


void test_bench(t_icplist *alist, t_icplist *blist, int total)
{
	quick_sort_a(alist, blist, 0, total);
	printf("counter %d\n", counter + ss_counter + sa_counter + sb_counter);
	printf("ss_counter %d\n", ss_counter);
	printf("sa_counter %d\n", sa_counter);
	printf("sb_counter %d\n", sb_counter);
}

