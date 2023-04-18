/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tim_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:03:48 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:03:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sorting.h"

int			split_arr(int *arr, int *lmr, int **left, int **right);

void		intersect(int *arr, int *lmr, int (*cmp)(int, int));

static void	insertionSort(int *arr, int left, int right, int (*cmp)(int, int))
{
    int i;
    int temp;
    int j;

    i = left + 1;
    while (i <= right)
    {
        temp = arr[i];
        j = i - 1;
        while (j >= left && cmp(arr[j], temp))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
        i++;
    }
}

static void	tim_merge(int *arr, int *lmr, int (*cmp)(int, int))
{
    int len1;
    int len2;
    int *left;
    int *right;

    if (cmp(arr[lmr[1] + 1], arr[lmr[1]]))
        return ;
    if (cmp(arr[lmr[0]], arr[lmr[2] - 1]))
    {
        if (split_arr(arr, lmr, &left, &right))
        {
            len1 = lmr[1] - lmr[0] + 1;
            len2 = lmr[2] - lmr[1];
            ft_memcpy(&arr[lmr[0]], right, len2 * sizeof(*arr));
            ft_memcpy(&arr[lmr[0] + len2], left, len1 * sizeof(*arr));
            free(left);
            free(right);
        }
        else
            return ;
    }
    else
        intersect(arr, lmr, cmp);
}

static int	helper_tern(int a, int b)
{
    if (a > b)
        return (b);
    return (a);
}

int			*tim_sort(int *arr, int n, int (*cmp)(int, int))
{
    int i;
    int size;
    int lmr[3];

    i = 0;
    while (i < n)
    {
        insertionSort(arr, i, helper_tern((i + TIM_SORT_RUN - 1), (n - 1)), cmp);
        i += TIM_SORT_RUN;
    }
    size = TIM_SORT_RUN;
    while (size < n)
    {
        lmr[0] = 0;
        while (lmr[0] < n)
        {
            lmr[1] = lmr[0] + size - 1;
            lmr[2] = helper_tern((lmr[0] + 2 * size - 1), (n - 1));
            if (lmr[1] < lmr[2])
                tim_merge(arr, lmr, cmp);
            lmr[0] += 2 * size;
        }
        size *= 2;
    }
    return (arr);
}
