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

#include "pushswap_checker.h"


int checker_solver(int ac, char **av)
{
	t_ps_stack	a_stack;
	t_ps_stack	b_stack;
	t_pscount 	counter;

	if (!ps_preprocess(&(a_stack.list), ac, av) \
	|| !ps_normalize(&(a_stack.list)))
		return (error_msg());
	b_stack.list = icplist_new((a_stack.list)->len, (a_stack.list)->pool);
	if (!b_stack.list)
	{
		icplist_destroy(&(a_stack.list), 0);
		return (malloc_failed());
	}
	setup_stack_a(&a_stack);
	setup_stack_b(&b_stack);
	set_counter_on_stack(&counter, a_stack.list->len);
	if (get_all_operations(&a_stack, &b_stack, &counter))
	{
		if (is_sorted(&a_stack, &b_stack))
			ok_message();
		else
			ko_message();
	}
	else
	{
		icplist_destroy(&(b_stack.list), 1);
		icplist_destroy(&(a_stack.list), 0);
		return (error_msg());
	}
	print_counter(&counter);
	ps_printlists(a_stack.list, b_stack.list, &printmembs);
	icplist_destroy(&(b_stack.list), 1);
	icplist_destroy(&(a_stack.list), 0);
	return (1);
}

/*
int main(int ac, char **av)
{
	if (ac > 1)
		checker_solver(--ac, ++av);
	return (0);
}*/

//gcc *.c -L. -lft -Iincs -o checker.exe
