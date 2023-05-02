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

static int prepare_lists_and_hashset(t_idmlist ***all_lists, t_ihs_table **table, int size)
{
	*all_lists = ft_calloc(size, sizeof(**all_lists));
	if (!*all_lists)
		return (malloc_failed());
	*table = ihs_init_table(size);
	if (!*table)
	{
		ft_free_set_null(all_lists);
		return (malloc_failed());
	}
	return (1);
}

static int free_all_lists(t_idmlist ***all_lists, int size)
{
	int			i;
	t_idmlist	**cur_list;

	if (*all_lists)
	{
		cur_list = *all_lists;
		i = 0;
		while (i < size && cur_list[i])
			idmlist_destroy(&cur_list[i++]);
		ft_free_set_null(all_lists);
	}
}

static int join_all_list_splits(t_idmlist ***all_lists, int size, char **args, int *total_args)
{
	int			check;
	int			split_count;
	int			i;
	t_idmlist	**cur_list;
	t_ihs_table	*table;

	check = 1;
	if(!prepare_lists_and_hashset(all_lists, &table, size))
		return (malloc_failed());
	cur_list = *all_lists;
	i = 0;
	while (i < size)
	{
		split_count = split_to_list(args[i], table, &cur_list[i]);
		if (split_count == -1)
		{
			check = 0;
			break;
		}
		else
			(*total_args) += split_count;
		i++;
	}
	ihs_free_table(&table);
	return (check);
}

static int lists_to_array(t_idmlist **all_lists, int **res, int total_count, int ac)
{
	t_idmnode	*cur;
	int			*arr;
	int			i;
	int			j;

	arr = malloc(sizeof(*arr) * total_count);
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (i < ac)
	{
		cur = all_lists[i++]->head;
		while (cur)
		{
			arr[j++] = cur->data;
			cur = cur->next;
		}
	}
	*res = arr;
	return (1);
}

int ps_preprocess(int **res, int ac, char **av, int *true_count)
{
	t_idmlist	**all_lists;
	int			*array;
	int			total_count;
	int			check;

	total_count = 0;
	check = 0;
	if (join_all_list_splits(&all_lists, ac, av, &total_count) \
	&& lists_to_array(all_lists, &array, total_count, ac))
	{
		check = 1;
		*true_count = total_count;
		*res = array;
	}
	free_all_lists(&all_lists, ac);
	return (check);
}
