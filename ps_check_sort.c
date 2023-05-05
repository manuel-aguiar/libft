#include "pushswap.h"

/*
t_icpnode *where_bucket_begins(t_ps_stack *stack, int min, int max)
{
	t_icpnode	*find;

	find = stack->list->pivot;
	if (stack->list->len == max - min)
		return (find);
	while (!(in_bucket(find->data, min, max) &&
	!in_bucket(find->prev->data, min, max)))
		find = find->prev;
	return (find);
}
*/
void	go_to_bucket_begins(t_ps_stack *stack, int min, int max, int options)
{
	int			position;
	t_icpnode	*find;

	position = 0;
	find = stack->list->pivot;
	if (stack->list->len == max - min)
		return ;
	while (!(in_bucket(find->data, min, max) &&
	!in_bucket(find->prev->data, min, max)))
	{
		find = find->prev;
		position--;
	}
	if (-position > stack->list->len / 2)
		pslist_rotate(stack, stack->list->len + position, options);
	else
		pslist_rotate(stack, position, options);

}

int	bucket_is_sorted(t_ps_stack *stack, int min, int max)
{
    t_icpnode *cur;

    if (stack->list->len == 1)
        return (1);
	cur = stack->list->pivot;
    if (stack->ascending)
	{
		while(cur->data == min && min < max)
		{
			cur = cur->next;
			min++;
		}
	}
	else
	{
		while(cur->data == (max - 1) && min < max)
		{
			cur = cur->next;
			max--;
		}
	}
	if (min == max)
		return (1);
	return (0);
}
