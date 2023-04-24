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

//gcc -Wall -Wextra -Werror *.c -L. -lft -Iincs

#include "pushswap.h"

void	printmembs(int num)
{
	ft_printf("%d   ", num);
}





void solver(int ac, char **av)
{
	int			*arr;
	t_pslist	*alist;
	t_pslist	*blist;

	blist = NULL;
	//ps_preprocess(&arr, ac, av);
	ft_atoi_arr(&arr, ac, av);

	ps_normalize(&arr, ac);
	ps_arr_to_cdlist(&alist, &arr, ac);
	blist = pslist_new(ac, alist->pool);
	ps_printlists(alist, blist, &printmembs);
	ps_split_list(alist, blist);
	if (blist->pivot->data != blist->max)
		pslist_rotate(blist, 1, "rb");
	//ps_merge_swap(alist, blist);
	//ps_bubble_sort(alist);
	ps_printlists(alist, blist, &printmembs);
	pslist_destroy(&blist, 1);
	pslist_destroy(&alist, 0);

}

int main(int ac, char **av)
{
	if (ac > 2)
		solver(--ac, ++av);
	return (0);
}
