/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:39:00 by marvin            #+#    #+#             */
/*   Updated: 2023/04/27 13:39:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int op_swap(t_icplist *alist, t_icplist *blist, char *op)
{
	if (!ft_strncmp(op, "sa\n", 3))
		pslist_swap_top(alist, NULL);
	else if (!ft_strncmp(op, "sb\n", 3))
		pslist_swap_top(blist, NULL);
	else if (!ft_strncmp(op, "ss\n", 3))
	{
		pslist_swap_top(alist, NULL);
		pslist_swap_top(blist, NULL);
	}
	else
		return (0);
	return (1);
}

int op_reverse_rotation(t_icplist *alist, t_icplist *blist, char *op)
{
	if (!ft_strncmp(op, "rra\n", 4))
		pslist_rotate(alist, -1, NULL);
	else if (!ft_strncmp(op, "rrb\n", 4))
		pslist_rotate(blist, -1, NULL);
	else if (!ft_strncmp(op, "rrr\n", 4))
	{
		pslist_rotate(alist, -1, NULL);
		pslist_rotate(blist, -1, NULL);
	}
	else
		return (0);
	return (1);
}

int op_rotation(t_icplist *alist, t_icplist *blist, char *op)
{
	if (!ft_strncmp(op, "ra\n", 3))
		pslist_rotate(alist, 1, NULL);
	else if (!ft_strncmp(op, "rb\n", 3))
		pslist_rotate(blist, 1, NULL);
	else if (!ft_strncmp(op, "rr\n", 3))
	{
		pslist_rotate(alist, 1, NULL);
		pslist_rotate(blist, 1, NULL);
	}
	else
		return (0);
	return (1);
}


int distribute_operations(t_icplist *alist, t_icplist *blist, char *op)
{
	if (!ft_strncmp(op, "ra\n", 3) || !ft_strncmp(op, "rb\n", 3) || !ft_strncmp(op, "rr\n", 3))
		op_rotation(alist, blist, op);
	else if (!ft_strncmp(op, "rra\n", 4) || !ft_strncmp(op, "rrb\n", 4) || !ft_strncmp(op, "rrr\n", 4))
		op_reverse_rotation(alist, blist, op);
	else if (!ft_strncmp(op, "sa\n", 3) || !ft_strncmp(op, "sb\n", 3) || !ft_strncmp(op, "ss\n", 3))
		op_swap(alist, blist, op);
	else if(!ft_strncmp(op, "pa\n", 3))
		pslist_push_top(alist, blist, NULL);
	else if(!ft_strncmp(op, "pb\n", 3))
		pslist_push_top(blist, alist, NULL);
	else
		return (0);
	return (1);
}


int	get_all_operations(t_icplist *alist, t_icplist *blist)
{
	char	*line;
	int		counter;
	int		check;

	check = 1;
	line = (char *)1;
	//ps_printlists(alist, blist, &printmembs);
	while (line && check)
	{

		line = get_next_line(0);
		if (line)
		{
			check = distribute_operations(alist, blist, line);
			//printf("%s", line);
			//ps_printlists(alist, blist, &printmembs);
			//printf("%s <- this is the line read, check gave %d\n", line, check);
			free(line);
		}
	}
	return (check);
}


int checker_solver(int ac, char **av)
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
	if (get_all_operations(alist, blist))
	{
		if (is_sorted(alist, blist))
			ok_message();
		else
			ko_message();
	}
	else
	{
		icplist_destroy(&blist, 1);
		icplist_destroy(&alist, 0);
		return (error_msg());
	}
	icplist_destroy(&blist, 1);
	icplist_destroy(&alist, 0);
	return (1);
}


int main(int ac, char **av)
{
	if (ac > 1)
		checker_solver(--ac, ++av);
	return (0);
}

//gcc *.c -L. -lft -Iincs -o checker.exe
