#include "pushswap.h"

int	bucket_is_sorted(t_ps_stack *stack, int min, int max, int ascending)
{
    t_icpnode *cur;

    if (stack->list->len == 1)
        return (1);
    cur = stack->list->pivot;
    if (ascending)
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
