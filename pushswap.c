/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:05 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 11:40:05 by marvin           ###   ########.fr       */
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

void solver(int ac, char **av)
{
	int *arr;
	t_icplist *list;

	if (ps_preprocess(&arr, ac, av))
		ft_putstr("that's great!\n");
	if (ps_normalize(&arr, ac))
		ft_putstr("porreiro pa!\n");
	if (ps_arr_to_cdlist(&list, &arr, ac))
		ft_putstr("tas a abusar da sorte....!\n");

}
/*
int main(int ac, char **av)
{
	if (ac > 1)
		solver(--ac, ++av);
	return (0);
}*/
