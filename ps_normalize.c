/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:50:17 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 11:50:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"



static int ascending(int a, int b)
{
    return (a > b);
}

static int countbigger(int *arr, int size, int target)
{
    int	i;
    int	res;

    i = 0;
    res = 0;
    while (i < size)
    {
        if (arr[i] > target)
            res++;
        i++;
    }
    return (res);
}

int normalize_slow(int **arr, int size)
{
    int	*new;
    int	i;
	int	*array;

    new = malloc(sizeof(*new) * size);
    if (!new)
	{
		*arr = NULL;
        return (0);
	}
	array = *arr;
    i = -1;
    while (++i < size)
	{
        new[i] = (size - 1 - countbigger(array, size, array[i]));
	}
	ft_memcpy(array, new, sizeof(*array) * size);
	free(new);
    return (1);
}

int	normalize_fast(int **arr, int size)
{
    int	*sorted;
    int	i;
	int	*array;

    sorted = malloc(sizeof(int) * size);
    if (!sorted)
	{
		*arr = NULL;
        return (0);
	}
	array = *arr;
    ft_memcpy(sorted, array, sizeof(int) * size);
    tim_sort(sorted, size, &ascending);
    i = -1;
    while (++i < size)
        array[i] = bin_srch(sorted, size, array[i], &ascending);
    free(sorted);
    return (1);
}

int	ps_normalize(int **arr, int size)
{
	if (size > 50)
		return (normalize_fast(arr, size));
	else
		return (normalize_slow(arr, size));
}
