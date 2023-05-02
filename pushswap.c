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

int solver(int ac, char **av)
{
	int			*arr;
	int			true_count;
	t_icplist	*alist;
	t_icplist	*blist;

	if (!ps_preprocess(&arr, ac, av, &true_count) \
	|| !ps_normalize(&arr, true_count) \
	|| !ps_arr_to_cdlist(&alist, &arr, true_count))
		return (error_msg());
	blist = icplist_new(true_count, alist->pool);
	if (!blist)
	{
		icplist_destroy(&alist, 0);
		return (malloc_failed());
	}

	if (!is_sorted(alist, blist))
		pushswap(alist, blist, true_count);
	//ft_printf("is it sorted? %d, total %d\n", bucket_is_sorted(alist, 0, true_count, 1), true_count);
	//ps_printlists(alist, blist, &printmembs);
	icplist_destroy(&blist, 1);
	icplist_destroy(&alist, 0);
	//printf("counter %d\n", counter + ss_counter + sa_counter + sb_counter);         //DELEEEEEEEEETE
	//printf("ss_counter %d\n", ss_counter);											//DELEEEEEEEEETE
	//printf("sa_counter %d\n", sa_counter);											//DELEEEEEEEEETE
	//printf("sb_counter %d\n", sb_counter);											//DELEEEEEEEEETE
	return (1);
}

/*
int main(int ac, char **av)
{
	if (ac > 1)
		solver(--ac, ++av);
	return (0);
}*/


//gcc *.c -L. -lft -Iincs -o push_swap.exe
