/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_banana.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:51:26 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 10:51:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
#include <stdio.h>
#include "pushswap.h"

void    solver(int *arr, int size);

void    testsolver(t_cdlist *a_list, t_cdlist *b_list, int size);

void pushswap_radix_split(t_cdlist *a_list, t_cdlist *b_list, int size)
{
    int i;
    int j;
    int max_num;
    int max_bits;
    int counter = 0;

    max_num = size - 1;
    max_bits = 0;
    while (max_num >> max_bits)
        max_bits++;
    j = 0;
    while (j < max_bits)
    {
        i = 0;
        printf("sorting bit %d\n", j);
        while (i < size)
        {
            //printf("cur data %d, j %d, op %d\n", a_list->pivot->data, j, ((a_list->pivot->data >> j) & 1));
            if (((a_list->pivot->data >> j) & 1) == 1)
            {
                cdlist_rotate(a_list, 1);
                printf("ra\n");
                counter++;
            }
            else
            {
                cdlist_push_top(b_list, a_list);
                printf("pb\n");
                counter++;
            }
            i++;
        }
        printf("list B: ");
        cdlist_head_print(b_list);
        printf("\nlist A: ");
        cdlist_head_print(a_list);
        printf("\n");
        while (b_list->pivot)
        {
            cdlist_push_top(a_list, b_list);
            printf("pa\n");
            counter++;
        }
        j++;
        printf("list B: ");
        cdlist_head_print(b_list);
        printf("\nlist A: ");
        cdlist_head_print(a_list);
        printf("\n\n");
    }
    printf("total operations were %d", counter);
}

int twopow(int nbr)
{
    int res = 2;

    if (nbr == 0)
        return (1);
    while (nbr-- > 1)
        res *= 2;
    return (res);
}

int totalzeros(int size, int bit)
{
    int division;
    int mod;
    int power;
    int ones;
    int left;

    power = twopow(bit + 1);
    division = size / power;
    mod = size % power;
    ones = power / 2;
    if (mod > ones)
        left = (mod - ones);
    else
        left = 0;
    return (size - (division * ones + left));
}

int total_radix_ops(int size)
{
    int max_bits;
    int i;
    int res;

    max_bits = 0;
    while ((size - 1) >> max_bits)
        max_bits++;
    res = size * max_bits;
    i = 0;
    while (i < max_bits)
        res += totalzeros(size, i++);
    return (res);
}

void    solver(int *arr, int size)
{
    int i;
    t_mpool *pool;
    t_cdlist *a_list;
    t_cdlist *b_list;

    pool = mpool_create(sizeof(t_cdnode), size);
    a_list = new_cdlist(size, pool);
    b_list = new_cdlist(size, pool);
    i = 0;
    while (i < size)
        cdlist_in_tail(a_list, arr[i++]);
    free(arr);
    testsolver(a_list, b_list, size);
    printlists(a_list, b_list);
    cdlist_destroy(&a_list, 1);
    cdlist_destroy(&b_list, 1);
    mpool_destroy(&pool);

}



void    testsolver(t_cdlist *a_list, t_cdlist *b_list, int size)
{
    int i;
    int scream;
    int counter;

    scream = rotatable(a_list);
    if (scream)
    {
        if (scream > 0)
            printmulti("ra", scream);
        else
            printmulti("rra", ABS(scream));
        return ;
    }
    counter = 0;
    while (a_list->pivot->data > a_list->pivot->prev->data)
    {
        cdlist_rotate(a_list, 1);
        printf("ra\n");
        counter++;
    }

    i = 0;
    while (b_list->len < size / 2 && i < size)
    {
        if (a_list->pivot->data > a_list->pivot->next->data && a_list->pivot->data != a_list->max && a_list->pivot->next->data != a_list->min)
        {
            cdlist_push_top(b_list, a_list);
            printf("pb\n");
            counter++;
        }
        else
        {
            cdlist_rotate(a_list, 1);
            printf("ra\n");
            counter++;
        }
        i++;
    }
    i = 0;
    while (i < size / 4)
    {
        if (a_list->pivot->data > a_list->pivot->next->data && a_list->pivot->next->data > a_list->min \
        && a_list->pivot->prev->data != a_list->pivot->data - 1 \
        && b_list->pivot->data < b_list->pivot->next->data && b_list->pivot->next->data < a_list->max \
        && b_list->pivot->prev->data != b_list->pivot->data - 1)
        {
            cdlist_swap_top(a_list);
            cdlist_swap_top(b_list);
            printf("ss\n");
            cdlist_rotate(a_list, 2);
            cdlist_rotate(b_list, 2);
            printf("rr\nrr\n");
            counter++;
        }
        else  if(is_magic_swap(a_list))
        {
            cdlist_swap_top(a_list);
            printf("sa\n");

        }
        else
        {
            cdlist_rotate(a_list, 1);
            cdlist_rotate(b_list, 1);
            printf("rr\n");
            counter++;
        }
        i++;
    }
    while (b_list->len > 0)
    {
        while (b_list->pivot->data > b_list->pivot->next->data)
        {
            cdlist_push_top(a_list, b_list);
            printf("pa\n");
            counter++;
        }
        if (a_list->pivot->data > a_list->pivot->next->data && a_list->pivot->next->data > a_list->min \
        && b_list->pivot->data < b_list->pivot->next->data && b_list->pivot->next->data < a_list->max)
        {
            cdlist_swap_top(a_list);
            cdlist_swap_top(b_list);
            printf("ss\n");
            cdlist_rotate(a_list, 2);
            cdlist_rotate(b_list, 2);
            printf("rr\nrr\n");
            counter++;
        }
        else if (b_list->len == 1)
        {
            cdlist_push_top(a_list, b_list);
            printf("pa\n");
            counter++;
        }
        else
        {
            cdlist_rotate(b_list, 1);
            printf("rb\n");
            counter++;
        }
    }
    if (scream = rotatable(a_list))
    {
        if (scream > 0)
            printmulti("ra\n", scream);
        else
            printmulti("rra\n", ABS(scream));
        return ;
    }
    printlists(a_list, b_list);
    if (counter > 0)
        testsolver(a_list, b_list, size);
}

int is_magic_swap(t_cdlist *list)
{
    if (list->pivot->data > list->pivot->prev->data && list->pivot->data > list->pivot->next->data \
    && list->pivot->next->data > list->pivot->prev->data)
        return (1);
    return (0);
}

int main(int ac, char **av)
{
    int *arr;
    int size;

    size = ft_atoi_arr(&arr, --ac, ++av);

    int *norm = normalize_slow(arr, size);

    printarray(norm, size);
    solver(norm, size);


    //free(norm);
    free(arr);


    printf("%d\n", total_radix_ops(500));
    return 0;
}

*/
