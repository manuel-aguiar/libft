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

static void 	swap_when_pushing(t_ps_stack *stack, int min, int max)
{
	t_icpnode *cur;

	cur = stack->list->pivot;
	if (((cur->data == cur->next->data + 1 && stack->ascending)\
	|| ((cur->data == cur->next->data - 1 && !stack->ascending)))
	&& !in_bucket(cur->data, min, max) \
	&& !in_bucket(cur->next->data, min, max))
		pslist_swap_top(stack, O_PRINT | O_COUNT);

}

void pushbucket(t_ps_stack *from, t_ps_stack *to, int min, int max)
{
    int size;
	int closest;
    size = max - min;

    while (size--)
    {
		closest = find_closest_in_bucket(from, min, max);
		if (closest < 0)
		{
			while (closest++ < 0)
			{
				swap_when_pushing(from, min, max);
				pslist_rotate(from, -1, O_PRINT | O_COUNT);
			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				swap_when_pushing(from, min, max);
				pslist_rotate(from, 1, O_PRINT | O_COUNT);
			}
		}
		super_swap(from, to, min, max);
        pslist_push_top(to, from, O_PRINT | O_COUNT);
    }
}

static void 	swap_when_inserting(t_ps_stack *stack, int target, int min, int max)
{
	t_icpnode *cur;

	if (stack->list->len <= 1)
		return ;
	cur = stack->list->pivot;
	if (((cur->data == cur->next->data + 1 && stack->ascending)
	|| (cur->data == cur->next->data - 1 && !stack->ascending)) \
	&& !is_target(cur->data, target) \
	&& !is_target(cur->next->data, target) \
	&& in_bucket(cur->data, min, max) \
	&& in_bucket(cur->next->data, min, max))
	{
		pslist_swap_top(stack, O_PRINT | O_COUNT);
	}
}

void 	put_target_to_top(t_ps_stack *stack, int target, int min, int max)
{
	int i;

	i = find_exact_target(stack, target);
    if (i > 0)
    {
        while (i--)
        {
            pslist_rotate(stack, 1, O_PRINT | O_COUNT);
			swap_when_inserting(stack, target, min, max);
        }
    }
    else
    {
        while (i++)
        {
            pslist_rotate(stack, -1, O_PRINT | O_COUNT);
			swap_when_inserting(stack, target, min, max);
        }
    }
}

void insertion_sort_push(t_ps_stack *to, t_ps_stack *from, int start, int end)
{
	int size;

	size = end - start;
	if (from->ascending)
	{
		while (size--)
		{
			put_target_to_top(from, start++, start, end);
			pslist_push_top(to, from, O_PRINT | O_COUNT);
		}
	}
	else
	{
		while (size--)
		{
			put_target_to_top(from, --end, start, end);
			pslist_push_top(to, from, O_PRINT | O_COUNT);
		}
	}
}
