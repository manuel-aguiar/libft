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

int sorted_forward(t_ps_stack *stack, int min, int max, int index)
{
	t_icpnode *cur;
	int len;
	int count;

	count = 0;
	cur = stack->list->pivot;
	len = max - min;
	//printf("checking sort forward:\n");
	//icplist_head_print(stack->list, &printmembs);
	//printf("index is %d value %d, min %d, max %d\n", index, stack->list->pivot->data, min, max);
	while (in_bucket(cur->next->data, min, max) && index < len - 1)
	{
		if ((cur->data > cur->next->data && stack->ascending)\
		|| (cur->data < cur->next->data && !stack->ascending))
		{
			//printf("forward returned KO, cur->data %d, cur->next %d, index %d\n", cur->data, cur->next->data, index );
			return (count);
		}
		cur = cur->next;
		index++;
		count++;
	}
	/*if ((cur->data != max - 1 && stack->ascending) \
	|| (cur->data != min && !stack->ascending))
	{
		//printf("forward returned OK\n");
		return (count);
	}*/
	//printf("forward returned BADDDDD\n");
	return (-1);
}

int sorted_backward(t_ps_stack *stack, int min, int max, int index)
{
	t_icpnode *cur;
	int count;

	count = -1;
	cur = stack->list->pivot;
	//printf("checking sort backward:\n");
	//icplist_head_print(stack->list, &printmembs);
	//printf("index is %d value %d, min %d, max %d\n", index, stack->list->pivot->data, min, max);
	while (in_bucket(cur->prev->data, min, max) && index > 0)
	{
		if ((cur->data < cur->prev->data && stack->ascending)\
		|| (cur->data > cur->prev->data && !stack->ascending))
		{
			//printf("backward returned KO, cur->data %d, cur->next %d index %d\n", cur->data, cur->prev->data, index);
			return (count);
		}
		cur = cur->prev;
		index--;
		count--;
	}
	/*if ((cur->data != min && stack->ascending) \
	|| (cur->data != max - 1 && !stack->ascending))
	{
		//printf("backward returned OK\n");
		return (count);
	}*/
	//printf("backward returned BAD\n");
	return (1);
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
		//while (i++ < len - best_index)
			pslist_rotate(stack, len - best_index, options);
	}
	else
	{
		//while (i++ < best_index)
			pslist_rotate(stack, best_index, options);
	}
	return (1);
}


void 	cocktail_two(t_ps_stack *stack, int min, int max, int options)
{
	go_to_bucket_begins(stack, min, max, options);
	pushswap_sort_two(stack, options);
}


void	stack_cocktail(t_ps_stack *stack, int min, int max, int options)
{
	int			i;
	int			len;
	int			rotate;
	//int 			count;

	//count = 0;

	if (max - min <= 2)
	{
		cocktail_two(stack, min, max, options);
		return ;
	}

	//printf("all good? min %d, max %d, stack %s, len %d\n", min, max, stack->push_name);
	//icplist_head_print(stack->list, &printmembs);
	//printf("  <--before moving to best, this is stack %s\n", stack->swap_name);
	if (get_stack_to_best_entry(stack, min, max, options))
		i = 0;
	else
		i = find_end_of_bucket(stack, min, max, options);
	//icplist_head_print(stack->list, &printmembs);
	//printf("  <--after moving to best\n");
	//printf("i is %d, min %d, max %d, size %d, so val at i should be %d, val at i is %d\n", i, min, max, max-min, min + i, stack->list->pivot->data);
	len = max - min;
	while (sorted_forward(stack, min, max, i) != -1 \
		|| sorted_backward(stack, min, max, i) != 1)
	{
		//printf("all good? min %d, max %d, stack %s\n", min, max, stack->swap_name);
		//icplist_head_print(stack->list, &printmembs);
		//count++;
		while (i < len - 2  && (rotate = sorted_forward(stack, min, max, i)) != -1)
		{
			pslist_rotate(stack, rotate, options);
			i += rotate;
			pushswap_sort_two(stack, options);
		}
		while (i > 0 && (rotate = sorted_forward(stack, min, max, i)) != 1)
		{
			pslist_rotate(stack, rotate, options);
			i += rotate;
			pushswap_sort_two(stack, options);
		}
		//if (count > 10)
		//{
			//printf("bank broke min %d, max %d, stack %s\n", min, max, stack->swap_name);
			//icplist_head_print(stack->list, &printmembs);
		//	exit(1);
		//}
	}
	if (stack->ascending)
		pslist_rotate(stack, find_exact_target(stack, min), options);
	else
		pslist_rotate(stack, find_exact_target(stack, max - 1), options);
}


void 	pushswap_sort_two(t_ps_stack *stack, int options)
{
	t_icpnode *cur;

	cur = stack->list->pivot;
	if ((cur->data > cur->next->data && stack->ascending) \
	|| (cur->data < cur->next->data && !stack->ascending))
		pslist_swap_top(stack, options);
}

void void_putstr(void *str)
{
	t_uchar *new;
	int i;

	new = (t_uchar *)str;
	write(1, new, ft_strlen(new) - 1);
	i = 0;
	while ((i++ < 5 - ft_strlen(new)))
		write(1, " ", 1);
}

void clean_putstr(void *str)
{
	t_uchar *new;
	int i;

	new = (t_uchar *)str;
	write(1, new, ft_strlen(new));
}

char *inst_equiv(t_ps_stack *send, t_ps_stack *receive, char *command)
{
	if (!ft_strncmp(command, send->push_name, ft_strlen(command)))
		return (receive->push_name);
	if (!ft_strncmp(command, send->swap_name, ft_strlen(command)))
		return (receive->swap_name);
	if (!ft_strncmp(command, send->rotate_name, ft_strlen(command)))
		return (receive->rotate_name);
	if (!ft_strncmp(command, send->revrot_name, ft_strlen(command)))
		return (receive->revrot_name);
	return (NULL);
}

char *combo_equiv(t_ps_stack *send, char *command)
{
	if (!ft_strncmp(command, send->swap_name, ft_strlen(command)))
		return (send->swap_combo);
	if (!ft_strncmp(command, send->rotate_name, ft_strlen(command)))
		return (send->rotate_combo);
	if (!ft_strncmp(command, send->revrot_name, ft_strlen(command)))
		return (send->revrot_combo);
	return (NULL);
}

t_vdmnode *vdmlist_retrieve_head(t_vdmlist **list)
{
	t_vdmnode *save;

	save = (*list)->head;
	if (!save->next)
	{
		(*list)->head = NULL;
		(*list)->tail = NULL;
		ft_free_set_null(list);
	}
	else
	{
		(*list)->head = save->next;
		if (!(*list)->head->next)
			(*list)->tail = (*list)->head;
		((*list)->len)--;
	}
	save->next = NULL;
	return (save);
}

void	vdmlist_node_to_tail(t_vdmlist *list, t_vdmnode *new_node)
{
	if (!list || !new_node)
		return ;
	if (list->tail)
    {
        new_node->prev = list->tail;
        list->tail->next = new_node;
    }
    else
        list->head = new_node;
    list->tail = new_node;
    ++(list->len);
}

char *find_common(t_ps_stack *lead, t_ps_stack *find, int *how_far)
{
	t_vdmnode *a;
	t_vdmnode *b;
	char *save;

	//printf("b is lead, now what, is there a list in b?\n");
	if (!lead->save_plays || !find->save_plays)
		return (NULL);
	a = lead->save_plays->head;
	b = find->save_plays->head;
	(*how_far) = 0;
	//printf("lead instruction is %s, find equiv is %s\n", a->data, inst_equiv(lead, find, a->data));
	while (b && ft_strncmp(b->data, inst_equiv(lead, find, a->data), ft_strlen(a->data)))
	{
		//printf("find->data %s, find_equiv %s\n", b->data, inst_equiv(lead, find, a->data));
		(*how_far)++;
		b = b->next;

	}
	if (!b)
	{
		//printf("instruction not found\n");
		(*how_far) = -1;
		return (NULL);
	}
	if (!ft_strncmp(b->data, inst_equiv(lead, find, a->data), ft_strlen(a->data)))
	{
		//printf("found instruction, it is %d away\n", *how_far);
		return (a->data);
	}
	return (NULL);
}


char *closest_common(t_ps_stack *a_stack, t_ps_stack *b_stack)
{
	int far_in_b;
	int far_in_a;
	char *common_a;
	char *common_b;

	common_a = find_common(a_stack, b_stack, &far_in_b);
	//printf("checking B top, B is lead\n");
	common_b = find_common(b_stack, a_stack, &far_in_a);
	//printf("common a %s how far in B %d\n, common b %s, how far in A %d\n", common_a, far_in_b, common_b, far_in_a);
	if (!common_a && !common_b)
		return (NULL);
	if (!common_a)
		return (common_b);
	if (!common_b)
		return (common_a);
	if (far_in_b > far_in_a)
		return (common_b);
	else
		return (common_a);
}

void	vdmlist_del_head_destroy(t_vdmlist **list, void(*del)(void *))
{
	vdmlist_del_head(*list, del);
	if (!(*list)->len)
		ft_free_set_null(list);
}

void intersect_plays(t_vdmlist *combo, t_ps_stack *a_stack, t_ps_stack *b_stack)
{
	char *target;
	char *equiv;

	while (a_stack->save_plays || b_stack->save_plays)
	{
		target = closest_common(a_stack, b_stack);
		//printf("target is %s\n", target);
		if (!target)
		{
			while (a_stack->save_plays)
				vdmlist_node_to_tail(combo, vdmlist_retrieve_head(&(a_stack->save_plays)));
			while (b_stack->save_plays)
				vdmlist_node_to_tail(combo, vdmlist_retrieve_head(&(b_stack->save_plays)));
		}
		else
		{
			equiv = inst_equiv(a_stack, b_stack, target);
			if (equiv)
			{
				while (a_stack->save_plays && ft_strncmp(a_stack->save_plays->head->data, target, ft_strlen(target)))
				{
					//printf("target is %s, a->top is %s, adding to combo\n", target, a_stack->save_plays->head->data);
					vdmlist_node_to_tail(combo, vdmlist_retrieve_head(&(a_stack->save_plays)));
				}
				while (b_stack->save_plays && ft_strncmp(b_stack->save_plays->head->data, equiv, ft_strlen(equiv)))
				{
					//printf("equivalent is %s, b->top is %s, adding to combo\n", equiv, b_stack->save_plays->head->data);
					vdmlist_node_to_tail(combo, vdmlist_retrieve_head(&(b_stack->save_plays)));
				}
				//printf("placing combo, equivalent is %s\n", combo_equiv(a_stack, target));
				vdmlist_in_tail(combo, ft_strdup(combo_equiv(a_stack, target)));
				//vdmlist_head_print(combo, &void_putstr);
				//printf("printing list so far\n");
				//printf("deleting a top \n");
				vdmlist_del_head_destroy(&(a_stack->save_plays), &free);
				//printf("deleting b top \n");
				vdmlist_del_head_destroy(&(b_stack->save_plays), &free);
				//printf("exit cool\n");
			}
			else
			{
				//printf("B IS TAKING THE LEAD FOR ONCE\n");
				equiv = inst_equiv(b_stack, a_stack, target);
				while (a_stack->save_plays && ft_strncmp(a_stack->save_plays->head->data, equiv, ft_strlen(equiv)))
					vdmlist_node_to_tail(combo, vdmlist_retrieve_head(&(a_stack->save_plays)));

				while (b_stack->save_plays && ft_strncmp(b_stack->save_plays->head->data, target, ft_strlen(target)))
					vdmlist_node_to_tail(combo, vdmlist_retrieve_head(&(b_stack->save_plays)));
				vdmlist_in_tail(combo, ft_strdup(combo_equiv(b_stack, target)));
				vdmlist_del_head_destroy(&(a_stack->save_plays), &free);
				vdmlist_del_head_destroy(&(b_stack->save_plays), &free);
			}
		}
		//vdmlist_head_print(combo, &void_putstr);
		//printf(" <-common list so far\n");
	}
	/*if (!a_stack->save_plays)
		printf("A plays destroyed, good\n");
	if (!b_stack->save_plays)
		printf("B plays destroyed, good\n");*/
}


void parallel_cocktail(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max)
{
	t_vdmlist *combo;
	int		mid;

	mid = (min + max) / 2;
	combo = vdmlist_new();
	//if (max - mid > 2)
	//printf("sending A to cocktail\n");
		stack_cocktail(a_stack, mid, max, O_SAVE | O_COUNT);
	//else
	//	pushswap_sort_two(a_stack, O_SAVE | O_COUNT);
	//if (mid - min > 2)
	//printf("sending B to cocktail\n");
		stack_cocktail(b_stack, min, mid, O_SAVE | O_COUNT);
	//else
	//	pushswap_sort_two(b_stack, O_SAVE | O_COUNT);
	intersect_plays(combo, a_stack, b_stack);
	//printf("printing group:\n");
	vdmlist_head_print(combo, &clean_putstr);
	vdmlist_destroy(&combo, &free);
	//printf("\nend of instructions\n");

}

/*	stack_cocktail(a_stack, mid, max, O_SAVE | O_COUNT);
	printf("printing instructions:\n");
	vdmlist_head_print(a_stack->save_plays, &void_putstr);
	printf("\n");
	stack_cocktail(b_stack, min, mid, O_SAVE | O_COUNT);
	vdmlist_head_print(b_stack->save_plays, &void_putstr);
	printf("\nend of instructions\n");*/


void pushswap_super_small(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max)
{
	int mid;

	mid = (min + max) / 2;
	pushbucket(a_stack, b_stack, min, mid);
	///ps_printlists(a_stack->list, b_stack->list, &printmembs);
	parallel_cocktail(a_stack, b_stack, min, max);
	/*if (max - mid > 2)
		stack_cocktail(a_stack, mid, max, O_PRINT | O_COUNT);
	else
		pushswap_sort_two(a_stack, O_PRINT | O_COUNT);
	if (mid - min > 2)
		stack_cocktail(b_stack, min, mid, O_PRINT | O_COUNT);
	else
		pushswap_sort_two(b_stack, O_PRINT | O_COUNT);*/
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
	insertion_sort_push(a_stack, b_stack, min, mid);
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
}






int trial(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max)
{

}
