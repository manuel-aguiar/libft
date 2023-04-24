/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_arr_to_cdlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:41 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 10:46:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ps_arr_to_cdlist(t_pslist **list, int **arr, int size)
{
	t_pslist *new;
	int i;
	int *array;

	new = pslist_new(size, NULL);
	if (new)
	{
		array = *arr;
		i = -1;
		while (++i < size)
			pslist_in_tail(new, array[i]);
	}
	*list = new;
	free(array);
	*arr = NULL;
	if (new)
		return (1);
	return (0);
}
