/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tim_sort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:03:53 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:03:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sorting.h"

int		split_arr(int *arr, int *lmr, int **left, int **right)
{
    int len1;
    int len2;
    int *l;
    int *r;

    len1 = lmr[1] - lmr[0] + 1;
    len2 = lmr[2] - lmr[1];
    l = malloc(len1 * sizeof(int));
    if (!l)
        return (0);
    r = malloc(len2 * sizeof(int));
    if (!right)
    {
        free(l);
        return (0);
    }
    ft_memcpy(l, &arr[lmr[0]], len1 * sizeof(*arr));
    ft_memcpy(r, &arr[lmr[1] + 1], len2 * sizeof(*arr));
    *left = l;
    *right = r;
    return (1);
}

void	intersect(int *arr, int *lmr, int (*cmp)(int, int))
{
    int *left;
    int *right;
    int i;
    int j;
    int k;

    if (split_arr(arr, lmr, &left, &right))
    {
        i = 0;
        j = 0;
        k = lmr[0];
        while (i < (lmr[1] - lmr[0] + 1) && j < (lmr[2] - lmr[1]))
        {
            if (cmp(right[j], left[i]))
                arr[k++] = left[i++];
            else
                arr[k++] = right[j++];
        }
        if (i < (lmr[1] - lmr[0] + 1))
            ft_memcpy(&arr[k], &left[i], ((lmr[1] - lmr[0] + 1) - i) * sizeof(*arr));
        if (j < (lmr[2] - lmr[1]))
            ft_memcpy(&arr[k], &right[j], ((lmr[2] - lmr[1]) - j) * sizeof(*arr));
        free(left);
        free(right);
    }
}
