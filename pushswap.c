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

//gcc *.c -L. -lft -Iincs


#include "pushswap.h"

void solver(int ac, char **av)
{
	int			*arr;
	t_icplist	*alist;
	t_icplist	*blist;

	blist = NULL;
	//ps_preprocess(&arr, ac, av);
	ft_atoi_arr(&arr, ac, av);

	ps_normalize(&arr, ac);
	ps_arr_to_cdlist(&alist, &arr, ac);
	blist = icplist_new(ac, alist->pool);
	ps_printlists(alist, blist, &printmembs);


	test_bench(alist, blist, ac);


	ps_printlists(alist, blist, &printmembs);
	icplist_destroy(&blist, 1);
	icplist_destroy(&alist, 0);
}

int main(int ac, char **av)
{
	if (ac > 2)
		solver(--ac, ++av);
	return (0);
}
