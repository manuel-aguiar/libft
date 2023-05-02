/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_int_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:49:02 by marvin            #+#    #+#             */
/*   Updated: 2023/05/02 10:49:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static size_t	wordnum(t_cchar *str)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (str[i] && !ft_isspace(str[i]))
		count++;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && ft_isspace(str[i - 1]))
			count++;
		i++;
	}
	return (count);
}

int atoi_overf(int res, char next, int *sign)
{
    int max;

    max = INT_MAX / 10;
    if (res < max)
        return (1);
    if (res > max)
    {
        *sign = 0;
        return (0);
    }
    else if (res == max)
    {
        if (*sign == 1 && next > INT_MAX % 10 + '0')
        {
            *sign = 0;
            return (0);
        }
        if (*sign == -1 && next > -(INT_MIN % 10) + '0')
        {
            *sign = 0;
            return (0);
        }
    }
    return (1);
}

static int	ps_atoiable(char **arg, int *placenum)
{
    int res;
    int sign;
	char *str;

	str = *arg;
    while (*str && ft_isspace(*str))
        str++;
    sign = 1;
    if (*str && *str == '-')
        sign = -1;
    if (*str && (*str == '-' || *str == '+'))
        str++;
    if (!ft_isdigit(*str))
        sign = 0;
    res = 0;
    while(*str && ft_isdigit(*str) && atoi_overf(res, *str, &sign))
        res = res * 10 - '0' + *str++;
    *placenum = res * sign;
    if (sign == 0)
        return (0);
	while (*str && !ft_isspace(*str))
        str++;
	*arg = str;
    return (1);
}

int		split_forthosewhothinkpushswapisonlyaboutparsing(char *arg, t_ihs_table	*table, t_idmlist **placelist)
{
	t_idmlist	*new_list;
	size_t		total_nums;
	size_t		i;
	int			num;

	if (!arg)
		return (-1);
	total_nums = wordnum(arg);
	new_list = idmlist_new();
	if (new_list)
	{
		i = 0;
		while (i < total_nums)
		{
			if(ps_atoiable(&arg, &num) && ihs_insert(table, num))
				idmlist_in_tail(new_list, num);
			else
				return (-1);
			i++;
		}
	}
	else
		return (-1);
	*placelist = new_list;
	return (total_nums);
}

static int prepare_dumb_arr_hash(t_idmlist ***all_lists, t_ihs_table **table, int size)
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

static int arrtoi_freesplitforthedumb(t_idmlist ***all_lists, int size, char **args, int *total_args)
{
	int			check;
	int			split_count;
	int			i;
	t_idmlist	**cur_list;
	t_ihs_table	*table;

	check = 1;
	if(!prepare_dumb_arr_hash(all_lists, &table, size))
		return (malloc_failed());
	cur_list = *all_lists;
	i = 0;
	while (i < size)
	{
		split_count = split_forthosewhothinkpushswapisonlyaboutparsing(args[i], table, &cur_list[i]);
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

int lists_to_array(t_idmlist **all_lists, int **res, int total_count, int ac)
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

int ps_superprocess(int **res, int ac, char **av, int *true_count)
{
	t_idmlist	**all_lists;
	int			*array;
	int			total_count;
	int			check;

	total_count = 0;
	check = 0;
	if (arrtoi_freesplitforthedumb(&all_lists, ac, av, &total_count) \
	&& lists_to_array(all_lists, &array, total_count, ac))
	{
		check = 1;
		*true_count = total_count;
		*res = array;
	}
	free_all_lists(&all_lists, ac);
	return (check);
}
