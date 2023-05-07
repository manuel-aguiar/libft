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

void setup_stack_b(t_ps_stack *b)
{
	b->save_plays = NULL;
	ft_memcpy(b->push_name, "pa\n\0", sizeof(b->push_name));
	ft_memcpy(b->swap_name, "sb\n\0", sizeof(b->swap_name));
	ft_memcpy(b->rotate_name, "rb\n\0", sizeof(b->rotate_name));
	ft_memcpy(b->revrot_name, "rrb\n\0", sizeof(b->revrot_name));
	ft_memcpy(b->swap_combo, "ss\n\0", sizeof(b->swap_combo));
	ft_memcpy(b->rotate_combo, "rr\n\0", sizeof(b->rotate_combo));
	ft_memcpy(b->revrot_combo, "rrr\n\0", sizeof(b->revrot_combo));
	b->ascending = 0;
	b->op_counter = 0;
	b->trial_mode = 0;
}

void setup_stack_a(t_ps_stack *a)
{
	a->save_plays = NULL;
	ft_memcpy(a->push_name, "pb\n\0", sizeof(a->push_name));
	ft_memcpy(a->swap_name, "sa\n\0", sizeof(a->swap_name));
	ft_memcpy(a->rotate_name, "ra\n\0", sizeof(a->rotate_name));
	ft_memcpy(a->revrot_name, "rra\n\0", sizeof(a->revrot_name));
	ft_memcpy(a->swap_combo, "ss\n\0", sizeof(a->swap_combo));
	ft_memcpy(a->rotate_combo, "rr\n\0", sizeof(a->rotate_combo));
	ft_memcpy(a->revrot_combo, "rrr\n\0", sizeof(a->revrot_combo));
	a->ascending = 1;
	a->op_counter = 0;
	a->trial_mode = 0;
}

int solver(int ac, char **av)
{
	t_ps_stack	a_stack;
	t_ps_stack	b_stack;

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
	if (!is_sorted(&a_stack, &b_stack))
		pushswap(&a_stack, &b_stack, a_stack.list->len);
	icplist_destroy(&(b_stack.list), 1);
	icplist_destroy(&(a_stack.list), 0);
	return (1);
}



int main(int ac, char **av)
{
	if (ac > 1)
		solver(--ac, ++av);
	return (0);
}

//gcc *.c -L. -lft -Iincs -o push_swap


//$args="    "; ./push_swap.exe $args | ./checker.exe $args




//args="    "; ./push_swap $args | ./checker $args
