#include "pushswap.h"

int	bucket_is_sorted(t_icplist *list, int min, int max, int ascending)
{
    t_icpnode *cur;
    
    if (list->len == 1)
        return (1);
    cur = list->pivot;
    if (ascending)
	{
		while(cur->data == min++ && min < max)
			cur = cur->next;
		if (min == max)
			return (1);
		return (0);
	}
	else
	{
		max--;
		while(cur->data == max-- && min <= max)
			cur = cur->next;
		if (min == max + 1)
			return (1);
		return (0);
	}
	return (1);
}
