/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_mergeswap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:13:22 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 13:13:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"


static int counter;

int	first_order(t_pslist *list)
{
	int piv;
	int next;

	piv = list->pivot->data;
	next = list->pivot->next->data;

	if (piv > next && !(piv == list->max && next == list->min))
		return (1);
	return (0);
}

int	second_order(t_pslist *list)
{
	int piv;
	int next;

	piv = list->pivot->data;
	next = list->pivot->next->next->data;

	if (piv > next && !(piv == list->max && next == list->min))
		return (1);
	return (0);
}

/*
int dumpable (t_pslist *alist, t_pslist *blist)
{
	while (alist->pivot->prev->data == blist->pivot->data)
}*/

void	get_max_on_top(t_pslist *blist)
{
	int i;
	t_psnode *cur;

	i = 0;
	cur = blist->pivot;
	while (cur->data != blist->max)
	{
		//ft_printf("cur->data %d, blist max %d\n", cur->data, blist->max);
		cur = cur->next;
		i++;
	}
	//printf("%d blist max, i is %d\n", blist->max, i);
	if (i <= blist->len / 2)
	{
		while (i--)
		{
			pslist_rotate(blist, 1, "rb");
			counter++;
		}
	}
	else
	{
		while (i--)
		{
			pslist_rotate(blist, -1, "rrb");
			counter++;
		}
	}
}

void 	find_b_place(t_pslist *blist, int target)
{
	t_psnode *cur;
	int i;

	if (target < blist->min || target > blist->max)
		get_max_on_top(blist);
	else
	{
		i = 0;
		cur = blist->pivot;
		while(!(cur->data > target && cur->next->data < target))
		{
			cur = cur->next;
			i++;
		}
		if (i < blist->len / 2)
		{
			while (i--)
			{
				pslist_rotate(blist, 1, "rb");
				counter++;
			}
		}
		else
		{
			while (i--)
			{
				pslist_rotate(blist, -1, "rrb");
				counter++;
			}
		}
	}
}


void ps_split_list(t_pslist *alist, t_pslist *blist)
{
	int len;

	len = alist->len;
	while (len--)
	{
		if (first_order(alist) && second_order(alist))
		{
			if (blist->len <= 1)
				pslist_push_top(blist, alist, "pb");
			else if (blist->len == 2)
			{
				if (blist->pivot->data < blist->pivot->next->data)
				{
					pslist_swap_top(alist, NULL);
					pslist_swap_top(blist, "ss");
					counter++;
					//ps_printlists(alist, blist, &printmembs);
				}
				else
				{
					pslist_push_top(blist, alist, "pb");
					counter++;
					//ps_printlists(alist, blist, &printmembs);
				}
			}
			else if (blist->len > 2)
			{
				//ps_printlists(alist, blist, &printmembs);

				find_b_place(blist, alist->pivot->data);
				pslist_push_top(blist, alist, "pb");
				counter++;
				//ps_printlists(alist, blist, &printmembs);
			}
		}
		else if (alist->pivot->data > alist->pivot->next->data && alist->pivot->data < alist->pivot->next->next->data)
		{
			if (blist->len >= 2)
			{
				if (blist->pivot->data < blist->pivot->next->data  && !(blist->pivot->data == blist->min && blist->pivot->next->data == blist->max))
				{
					pslist_swap_top(alist, NULL);
					pslist_swap_top(blist, "ss");
					counter++;
					//ps_printlists(alist, blist, &printmembs);
				}
				else
				{
					pslist_swap_top(alist, "sa");
					counter++;
					//ps_printlists(alist, blist, &printmembs);
				}
			}
			else
			{
				pslist_swap_top(alist, "sa");
				counter++;
			}
		}
		else
		{
			pslist_rotate(alist, 1, "ra");
			counter++;
			//ps_printlists(alist, blist, &printmembs);
		}
	}
	//ps_printlists(alist, blist, &printmembs);
}


int	closest_gap_forward(t_pslist *list)
{
	int piv;
	int next;
	int count;
	t_psnode *cur;

	count = 0;
	cur = list->pivot;
	piv = cur->data;
	next = cur->next->data;
	while (next - piv == 1 || (piv == list->max && next == list->min))
	{
		cur = cur->next;
		piv = cur->data;
		next = cur->next->data;
		count++;
	}
	return (count);
}

int	closest_gap_backward(t_pslist *list)
{
	int piv;
	int prev;
	int count;
	t_psnode *cur;

	count = 0;
	cur = list->pivot;
	piv = cur->data;
	prev = cur->prev->data;
	while (piv - prev == 1 || (piv == list->min && prev == list->max))
	{
		cur = cur->prev;
		piv = cur->data;
		prev = cur->prev->data;
		count++;
	}
	return (count);
}

void	closest_gap(t_pslist *list)
{
	int count_front;
	int count_back;

	count_front = closest_gap_forward(list);
	count_back = closest_gap_backward(list);

}

void	ps_merge_swap(t_pslist *alist, t_pslist *blist)
{
	while (blist->len)
	{
		while (blist->len && ((blist->pivot->data == blist->max && alist->pivot->data == alist->min) || alist->pivot->data == blist->pivot->data + 1))
		{
			//ps_printlists(alist, blist, &printmembs);
			pslist_push_top(alist, blist, "pa");
			counter++;
		}

		while (blist->len && (alist->pivot->data != blist->pivot->data + 1))
		{
			//ps_printlists(alist, blist, &printmembs);
			pslist_rotate(alist, -1, "rra");
			counter++;
		}
		if (!blist->len ||(blist->pivot->next != blist->pivot && blist->pivot-> data < blist->pivot->next->data))
			break;
	}
	ft_printf("number of operations was %d\n", counter);
	//ps_printlists(alist, blist, &printmembs);
}

