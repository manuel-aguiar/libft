/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_preprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:28:31 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 11:28:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

#define MAGIC_SIZE 200

static int checkdups(int size, int *arr, int target)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (target == arr[i])
			return (0);
		i++;
	}
	arr[size] = target;
	return (1);
}

static int arrtoi_naivedups(int **res, int size, char **args)
{
	int *arr;
	int i;
	int num;

	arr = malloc(size * sizeof(*arr));
	if (!arr)
	{
		*res = NULL;
		return (0);
	}
	i = 0;
	while (i < size)
	{
		if (ft_atoiable(args[i], &num) && checkdups(i, arr, num))
			i++;
		else
		{
			free(arr);
			*res = NULL;
			return (0);
		}
	}
	*res = arr;
	return (1);
}

static int arrtoi_tabledups(int **res, int size, char **args)
{
	int *arr;
	int i;
	int num;
	t_ihs_table *table;

	table = ihs_init_table(size);
	arr = malloc(size * sizeof(*arr));
	if (!arr | !table)
	{
		*res = NULL;
		return (0);
	}
	i = 0;
	while (i < size)
	{
		if (ft_atoiable(args[i], &num) && ihs_insert(table, num))
			arr[i++] = num;
		else
		{
			free(arr);
			*res = NULL;
			return (0);
		}
	}
	ihs_free_table(&table);
	*res = arr;
	return (1);
}

static int ps_is_sorted(int *arr, int size)
{
	int i;

	i = 1;
	while (i < size)
	{
		if (arr[i] < arr[i - 1])
			return (0);
		i++;
	}
	return (1);
}

int ps_preprocess(int **res, int ac, char **av)
{
	int check;
	if (ac > MAGIC_SIZE)
		check = arrtoi_tabledups(res, ac, av);
	else
		check = arrtoi_naivedups(res, ac, av);
	if (check && !ps_is_sorted(*res, ac))
		return (1);
	free(*res);
	*res = NULL;
	return (0);
}
