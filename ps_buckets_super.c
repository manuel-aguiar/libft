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

int     in_bucket(int target, int min, int max)
{
    return ((target >= min && target < max));
}

void 	put_target_to_bottom(t_pslist *blist, int target)
{
	t_psnode *cur;
	int i;

    i = 0;
    cur = blist->pivot;
    while(cur->prev->data != target)
    {
        cur = cur->next;
        i++;
    }
    if (i <= blist->len / 2)
    {
        while (i--)
        {
            pslist_rotate(blist, 1, "ra");
            counter++;
        }
    }
    else
    {
        i = blist->len - i;
        while (i--)
        {
            pslist_rotate(blist, -1, "rra");
            counter++;
        }
    }
}

void 	put_target_to_top(t_pslist *blist, int target)
{
	t_psnode *cur;
	int i;

    i = 0;
    cur = blist->pivot;
    while(cur->data != target)
    {
        cur = cur->next;
        i++;
    }
    if (i <= blist->len / 2)
    {
        while (i--)
        {
            pslist_rotate(blist, 1, "ra");
            counter++;
        }
    }
    else
    {
        i = blist->len - i;
        while (i--)
        {
            pslist_rotate(blist, -1, "rra");
            counter++;
        }
    }
}

int find_closest_in_bucket(t_pslist *list, int min, int max)
{
	t_psnode *cur;
	int countpos;
	int countneg;

	countpos = 0;
	countneg = 0;
	cur = list->pivot;
	while (!in_bucket(cur->data, min, max))
	{
		cur = cur->next;
		countpos++;
	}
	cur = list->pivot;
	while (!in_bucket(cur->data, min, max) && -countneg < countpos)
	{
		cur = cur->prev;
		countneg--;
	}
	if (-countneg >= countpos)
		return (countpos);
	return (countneg);
}

void pushbucket_to_b(t_pslist *alist, t_pslist *blist, int min, int max)
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
				pslist_rotate(alist, -1, "rra");
				counter++;
			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				pslist_rotate(alist, 1, "ra");
				counter++;
			}
		}
        pslist_push_top(blist, alist, "pb");
		//ps_printlists(alist, blist, &printmembs);
        counter++;
    }
}

/* SE LEN = SIZE, NUNCA FOI PARTIDO, ENCHE O BUCKET ASAP E VAI PARA O PONTO ONDE O COMPLEMENTO TERMINA*/

void pushbucket_to_a(t_pslist *alist, t_pslist *blist, int min, int max)
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
				pslist_rotate(blist, -1, "rrb");
				counter++;
			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				pslist_rotate(blist, 1, "rb");
				counter++;
			}
		}
        pslist_push_top(alist, blist, "pa");
		counter++;
	}
}

void insertion_sort_to_b(t_pslist *to, t_pslist *from, int start, int end)
{
	int size;

	size = end - start;
	while (size--)
	{
		put_target_to_top(from, start++);
		pslist_push_top(to, from, "pb");
		counter++;
	}
}

void	insertion_sort_to_a(t_pslist *to, t_pslist *from, int start, int end)
{
	int size;

	size = end - start;
	while (size--)
	{
		put_target_to_top(from, --end);
		pslist_push_top(to, from, "pa");
		counter++;
	}
}

int find_end_of_bucket(t_pslist *list, int min, int max)
{
	int countpos;
	int countneg;
	t_psnode *cur;

	countpos = 0;
	countneg = 0;
	cur = list->pivot;
	while (!(in_bucket(cur->data, min, max) && !in_bucket(cur->prev->data, min, max))
	&& countpos < list->len + 1)
	{
		cur = cur->next;
		countpos++;
	}
	if (countpos >= list->len)
		return (0);
	if (countpos > list->len / 2)
		return (countpos - list->len);
	return (countpos);
}

void move_to_end_of_bucket(t_pslist *list, int min, int max)
{
	int move;


	move = find_end_of_bucket(list, min, max);
	printf("calling bucket move, move is %d\n", move);
	if (!move)
		return ;
	if (move > 0)
	{
		while (move--)
		{
			pslist_rotate(list, 1, "rb");
			printf("end of bucket rotate\n");
			counter++;
		}
	}
	if (move < 0)
	{
		while (move++)
		{
			pslist_rotate(list, -1, "rrb");
			printf("end of bucket reverse rotate\n");
			counter++;
		}
	}
}

void quick_sort_a(t_pslist *alist, t_pslist *blist, int start, int end);
void quick_sort_b(t_pslist *alist, t_pslist *blist, int start, int end);

void quick_sort_b(t_pslist *alist, t_pslist *blist, int start, int end)
{
	int mid;

	mid = (start + end) / 2;
	if (end - start < 15)
	{
		printf("calling INSERTION SORT to A to finish, start %d, mid %d, counter %d\n", start, end, counter);
		ps_printlists(alist, blist, &printmembs);
		insertion_sort_to_a(alist, blist, start, end);
		ps_printlists(alist, blist, &printmembs);
		return ;
	}
	printf("pushing to A, mid %d, end %d, counter %d\n", mid, end, counter);
	pushbucket_to_a(alist, blist, mid, end);

	ps_printlists(alist, blist, &printmembs);

	printf("calling quicksort A, sending inputs mid %d, end %d\n", mid, end);
	quick_sort_a(alist, blist, mid, end);

	printf("calling quicksort B recursively, sending inputs mid %d, end %d\n", start, mid);
	quick_sort_b(alist, blist, start, mid);

}

void quick_sort_a(t_pslist *alist, t_pslist *blist, int start, int end)
{
	int mid;

	mid = (start + end) / 2;

	if (end - start < 15)
	{
		printf("calling INSERTION SORT to B to finish, start %d, mid %d, counter %d\n", start, end, counter);
		ps_printlists(alist, blist, &printmembs);
		insertion_sort_to_b(blist, alist, start, end);
		pushbucket_to_a(alist, blist, start, end);
		ps_printlists(alist, blist, &printmembs);
		return ;
	}
	printf("pushing to B, start %d, mid %d, counter %d\n", start, (start + end) / 2, counter);
	pushbucket_to_b(alist, blist, start, (start + end) / 2);
	ps_printlists(alist, blist, &printmembs);

	printf("calling quicksort A recursively to sort the second half, sending inputs start %d, mid %d\n", mid, end);
	quick_sort_a(alist, blist, mid, end);
	printf("calling quicksort B, sending inputs start %d, mid %d\n", start, mid);
	quick_sort_b(alist, blist, start, mid);

}


void test_bench(t_pslist *alist, t_pslist *blist, int total)
{
	quick_sort_a(alist, blist, 0, total);

/*
	printf("pushing to B from %d, to %d, counter %d\n",  50, 75, counter);
	pushbucket_to_b(alist, blist,  50, 75);
	ps_printlists(alist, blist, &printmembs);

	printf("pushing to B from %d, to %d, counter %d\n",  75, 87, counter);
	pushbucket_to_b(alist, blist, 75, 87);
	ps_printlists(alist, blist, &printmembs);

	printf("pushing to B from %d, to %d, counter %d\n",  87, 94, counter);
	pushbucket_to_b(alist, blist, 87, 94);
	ps_printlists(alist, blist, &printmembs);

	printf("insertion sort to B from %d, to %d, counter %d\n",  94, 100, counter);
	insertion_sort_to_b(blist, alist, 94, 100);
	ps_printlists(alist, blist, &printmembs);

	printf("pushing to A from %d, to %d, counter %d\n",  25, 50, counter);
	pushbucket_to_a(alist, blist, 25, 50);
	ps_printlists(alist, blist, &printmembs);*/


/*
	printf("pushing to A from %d, to %d, counter %d\n",  0, 25, counter);
	pushbucket_to_a(alist, blist, 0, 25);
	ps_printlists(alist, blist, &printmembs);

	printf("pushing to A from %d, to %d, counter %d\n",  25, 37, counter);
	pushbucket_to_a(alist, blist,  25, 37);
	ps_printlists(alist, blist, &printmembs);

	printf("pushing to B from %d, to %d, counter %d\n",  75, 87, counter);
	pushbucket_to_b(alist, blist, 75, 87);*/



	printf("counter %d\n", counter);
}

