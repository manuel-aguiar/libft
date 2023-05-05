/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_preprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:34:32 by marvin            #+#    #+#             */
/*   Updated: 2023/05/02 15:34:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*static int		check_duplicates(int *target, int *zero, int *num_xor)
{
	int test;
	printf("target %d, zero %d xor_res %d before xor with target\n", *target, *zero, *num_xor);
	if (*target == 0)
	{
		if (!*zero)
		{
			*zero = 1;
			return (1);
		}
		else
			return (1);
	}
	(*num_xor) ^= *target;
	printf("target %d, zero %d xor_res %d after xor with target\n", *target, *zero, *num_xor);
	test = *num_xor;
	if (test ^= *target)
		return (1);
	return (1);
}*/

static int
split_to_list(t_idmlist *list, char *arg, int *zero, int *num_xor)
{
	int			total_nums;
	int			i;
	int			num;

	if (!arg || !*arg || !(total_nums = wordnum(arg)))
		return (0);
	i = 0;
	while (i < total_nums)
	{
		if(ps_atoiable(&arg, &num) \
		&& idmlist_in_tail(list, num))
			i++;
		else
			return (0);
	}
	return (total_nums);
}

static int join_all_splits(t_idmlist **list, int size, char **args)
{
	int	check;
	int	i;
	int	zero;
	int num_xor;

	zero = 0;
	num_xor = 0;
	check = 1;
	*list = idmlist_new();
	if (!*list)
		return (0);
	i = 0;
	while (i < size)
	{
		if (!split_to_list(*list, args[i], &zero, &num_xor))
		{
			check = 0;
			idmlist_destroy(list);
			break;
		}
		i++;
	}
	return (check);
}

static int list_dmalloc_to_cpool(t_icplist **final, t_idmlist **list)
{
	t_icplist	*new;
	t_idmlist	*old;
	int			i;

	new = icplist_new((*list)->len, NULL);
	if (!new)
	{
		idmlist_destroy(list);
		return (0);
	}
	old = *list;
	while (old->head)
	{
		icplist_in_tail(new, old->head->data);
		idmlist_del_head(old);
	}
	idmlist_destroy(list);
	*final = new;
	return (1);
}


/*static int check_duplicates(t_icplist **final)
{
	t_ihs_table	*table;
	t_icpnode	*cur;
	int			i;


	if (!*final)
		return (0);
	table = ihs_init_table((*final)->len);
	if (!table)
		return (0);
	cur = (*final)->pivot;
	i = 0;
	while (i < (*final)->len)
	{
		if (!ihs_insert(table, cur->data))
		{
			icplist_destroy(final, 0);
			ihs_free_table(&table);
			return (0);
		}
		i++;
		cur = cur->next;
	}
	ihs_free_table(&table);
	return (1);
}*/


int ps_preprocess(t_icplist **final, int ac, char **av)
{
	t_idmlist	*list;

	if (join_all_splits(&list, ac, av) \
	&& list_dmalloc_to_cpool(final, &list))
		return (1);
	return (0);
}
