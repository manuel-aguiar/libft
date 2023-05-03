/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:50:17 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 11:50:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int ascending(int a, int b)
{
    return (a > b);
}

static int copy_icplist_to_array(t_icplist *list, int **place)
{
	t_icpnode	*cur;
	int			*arr;
	int			len;
	int			i;

	len = list->len;
	arr = malloc(sizeof(int) * list->len);
	if (!arr)
		return (0);
	cur = list->pivot;
	i = 0;
	while (i < len)
	{
		arr[i] = cur->data;
		cur = cur->next;
		i++;
	}
	*place = arr;
	return (1);
}

static int	normalize_list(t_icplist *list)
{
    t_icpnode	*cur;
	int			*sorted;
	int			len;
    int			i;

    if (!copy_icplist_to_array(list, &sorted))
		return (0);
	len = list->len;
    if(!tim_sort(sorted, len, &ascending))
	{
		ft_free_set_null(&sorted);
		return (0);
	}
	cur = list->pivot;
    i = 0;
    while (i++ < len)
	{
		cur->data = bin_srch(sorted, len, cur->data, &ascending);
		cur = cur->next;
	}
    free(sorted);
    return (1);
}

int	ps_normalize(t_icplist **final)
{
	if (!normalize_list(*final))
	{
		icplist_destroy(final, 0);
		return (0);
	}
	return (1);
}
