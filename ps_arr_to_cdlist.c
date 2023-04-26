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

int	ps_arr_to_cdlist(t_icplist **list, int **arr, int size)
{
	t_icplist *new;
	int i;
	int *array;

	new = icplist_new(size, NULL);
	if (new)
	{
		array = *arr;
		i = -1;
		while (++i < size)
			icplist_in_tail(new, array[i]);
	}
	*list = new;
	free(array);
	*arr = NULL;
	if (new)
		return (1);
	return (0);
}

void	ps_printlists(t_icplist *a_list, t_icplist *b_list, void (*pnt)(int))
{
	ft_printf("list B: ");
	icplist_head_print(b_list, pnt);
	ft_printf("\nlist A: ");
	icplist_head_print(a_list, pnt);
	ft_printf("\n");
}

void	printmembs(int num)
{
	ft_printf("%d   ", num);
}
