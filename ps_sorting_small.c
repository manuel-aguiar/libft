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

int correct_place(t_icpnode *node, int len, int start)
{
	t_icpnode *cur;
	t_icpnode *comp;
	int count;
	int i;
	int j;

	comp = node;
	cur = comp;
	i = 0;
	while (i < start)
	{
		comp = comp->next;
		i++;
	}
	count = 0;
	j = 0;
	while (j++ < len)
	{
		if (cur->data < comp->data)
			count++;
		cur = cur->next;
	}
	//printf("tested value %d at index %d count of #'s lower than itself %d, should be %d places to the side\n", comp->data, i, count, ABS((i - count)));
	return (ABS((i - count)));
}

int score_sum(t_icpnode *node, int len)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (i < len)
	{
		res += correct_place(node, len, i);
		i++;
	}
	return (res);
}

int closest_path(int index, int len)
{
	if (index > len / 2)
		return (len - index);
	else
		return (index);
}

int best_cocktail_entry(t_ps_stack *stack, int len)
{
	t_icpnode	*cur;
	int			best_index;
	int			best_score;
	int			comp;
	int			i;

	best_index = 0;
	i = 0;
	cur = stack->list->pivot;
	while (i < len)
	{
		//printf("testing from data point %d, index %d\n", cur->data, i);
		if (i == 0)
			best_score = score_sum(cur, len);
		else
		{
			comp = score_sum(cur, len) + closest_path(i, len);
			//printf("got total score of %d\n", comp);
			if (comp < best_score)
			{
				best_index = i;
				best_score = comp;
			}
		}
		//printf("best score so far is %d at index %d\n", best_score, best_index);
		i++;
		cur = cur->next;
	}
	return (best_index);
}

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

int sorted_forward(t_ps_stack *stack, int min, int max, int index)
{
	t_icpnode *cur;
	int len;

	cur = stack->list->pivot;
	len = max - min;
	//printf("checking sort forward:\n");
	//icplist_head_print(stack->list, &printmembs);
	//printf("index is %d value %d, min %d, max %d\n", index, stack->list->pivot->data, min, max);
	while (in_bucket(cur->next->data, min, max) && index < len - 1)
	{
		if ((cur->data != cur->next->data - 1  && stack->ascending)\
		|| (cur->data != cur->next->data + 1 && !stack->ascending))
		{
			//printf("forward returned KO, cur->data %d, cur->next %d, index %d\n", cur->data, cur->next->data, index );
			return (0);
		}
		cur = cur->next;
		index++;
	}
	if ((cur->data == max - 1 && stack->ascending) \
	|| (cur->data == min && !stack->ascending))
	{
		//printf("forward returned OK\n");
		return (1);
	}
	//printf("forward returned BADDDDD\n");
	return (0);
}

int sorted_backward(t_ps_stack *stack, int min, int max, int index)
{
	t_icpnode *cur;

	cur = stack->list->pivot;
	//printf("checking sort backward:\n");
	//icplist_head_print(stack->list, &printmembs);
	//printf("index is %d value %d, min %d, max %d\n", index, stack->list->pivot->data, min, max);
	while (in_bucket(cur->prev->data, min, max) && index > 0)
	{
		if ((cur->data != cur->prev->data + 1  && stack->ascending)\
		|| (cur->data != cur->prev->data - 1 && !stack->ascending))
		{
			//printf("backward returned KO, cur->data %d, cur->next %d index %d\n", cur->data, cur->prev->data, index);
			return (0);
		}
		cur = cur->prev;
		index--;
	}
	if ((cur->data == min && stack->ascending) \
	|| (cur->data == max - 1 && !stack->ascending))
	{
		//printf("backward returned OK\n");
		return (1);
	}
	//printf("backward returned BAD\n");
	return (0);
}

t_icpnode *get_stack_to_place(t_ps_stack *stack, int current, int target, int options)
{
	int len;
	int i;
	int move;

	len = stack->list->len;
	i = 0;
	move = len - current + target;
	if (move > len / 2)
	{
		while (i++ < len - move)
			pslist_rotate(stack, -1, options);
	}
	else
	{
		while (i++ < move)
			pslist_rotate(stack, 1, options);
	}
	return (stack->list->pivot);
}

int		bucket_is_alone_in_list(t_ps_stack *stack, int min, int max)
{
	t_icpnode *cur;
	int size;
	int i;

	size = max - min + 1;
	cur = stack->list->pivot;
	i = 0;
	while (i < size && in_bucket(cur->data, min, max))
	{
		cur = cur->next;
		i++;
	}
	if (i == size)
		return (1);
	return (0);
}

int find_end_of_bucket(t_ps_stack *stack, int min, int max, int options)
{
	t_icpnode *cur;
	int i;
	int size;
	int closest;

	size = max - min;
	cur = stack->list->pivot;
	if (!in_bucket(cur->data, min, max))
	{
		closest = find_closest_in_bucket(stack, min, max);
		pslist_rotate(stack, closest, options);
		if (closest > 0)
			return (0);
		else
			return (size - 1);
	}
	i = 0;
	while (in_bucket(cur->next->data, min, max))
	{
		cur = cur->next;
		i++;
	}
	return (size - i - 1);
}

int get_stack_to_best_entry(t_ps_stack *stack, int min, int max, int options)
{
	int len;
	int best_index;
	int i;

	if (!bucket_is_alone_in_list(stack, min, max))
		return (0);
	len = stack->list->len;
	best_index = best_cocktail_entry(stack, stack->list->len);
	i = 0;
	if (best_index > len / 2)
	{
		while (i++ < len - best_index)
			pslist_rotate(stack, -1, options);
	}
	else
	{
		while (i++ < best_index)
			pslist_rotate(stack, 1, options);
	}
	return (1);
}


void	stack_cocktail(t_ps_stack *stack, int min, int max, int options)
{
	int			i;
	int			len;
	//int 			count;

	//count = 0;

	//icplist_head_print(stack->list, &printmembs);
	//printf("  <--before moving to best\n");
	if (get_stack_to_best_entry(stack, min, max, options))
		i = 0;
	else
	{
		i = find_end_of_bucket(stack, min, max, options);
	}
	//icplist_head_print(stack->list, &printmembs);
	//printf("  <--after moving to best\n");
	//printf("i is %d, min %d, max %d, size %d, so val at i should be %d, val at i is %d\n", i, min, max, max-min, min + i, stack->list->pivot->data);
	len = max - min;
	while (!sorted_forward(stack, min, max, i) || !sorted_backward(stack, min, max, i))
	{
		//count++;
		//printf("in loop?\n");
		pushswap_sort_two(stack, options);
		while (i < len - 2  && !sorted_forward(stack, min, max, i))
		{
			pslist_rotate(stack, 1, options);
				i++;
			pushswap_sort_two(stack, options);
			//icplist_head_print(stack->list, &printmembs);
			//printf("  <--front moving\n");

		}
		while (i > 0 && !sorted_backward(stack, min, max, i))
		{
			pslist_rotate(stack, -1, options);
				i--;
			pushswap_sort_two(stack, options);
			//icplist_head_print(stack->list, &printmembs);
			//printf("  <--back moving\n");
		}
		/*if (count > 20)
		{
			printf(" BREAKING\nBREAKING\n");
			break ;
		}*/
	}
	//printf("exiting cockktail\n");
	put_target_to_top(stack, min, min, max);
}


void 	pushswap_sort_two(t_ps_stack *stack, int options)
{
	t_icpnode *cur;

	cur = stack->list->pivot;
	if ((cur->data > cur->next->data && stack->ascending) \
	|| (cur->data < cur->next->data && !stack->ascending))
		pslist_swap_top(stack, options);
}


void pushswap_super_small(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max)
{
	int mid;

	mid = (min + max) / 2;
	pushbucket(a_stack, b_stack, min, mid);
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
	printf("sorting stack a\n");
	if (a_stack->list->len == 2)
		pushswap_sort_two(a_stack, O_PRINT | O_COUNT);
	else
		stack_cocktail(a_stack, mid, max, O_PRINT | O_COUNT);
	printf("sorting stack b\n");
	if (b_stack->list->len == 2)
		pushswap_sort_two(b_stack, O_PRINT | O_COUNT);
	else
		stack_cocktail(b_stack, min, mid, O_PRINT | O_COUNT);
	printf("ending sorting b\n");
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
	insertion_sort_push(a_stack, b_stack, min, mid);
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
}


int trial(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max)
{

}
