/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_list_mpool_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:51:40 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:51:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void pslist_del_head(t_pslist* list)
{
    t_psnode *cur;
    t_psnode *new_pivot;

    if (!list || !(list->pivot))
        return ;
    cur = list->pivot;
    if (list->len > 1)
    {
        new_pivot = cur->next;
        new_pivot->prev = cur->prev;
        cur->prev->next = new_pivot;
        list->pivot = new_pivot;
    }
    else
        list->pivot = NULL;
    mpool_dealloc(list->pool, cur);
    --(list->len);
}

void pslist_del_tail(t_pslist* list)
{
    t_psnode *cur;
    t_psnode *cur_pivot;

    if (!list || !(list->pivot))
        return ;
    cur = list->pivot->prev;
    if (list->len > 1)
    {
        cur_pivot = cur->next;
        cur_pivot->prev = cur->prev;
        cur->prev->next = cur_pivot;
    }
    else
        list->pivot = NULL;
    mpool_dealloc(list->pool, cur);
    --(list->len);
}

void pslist_head_print(t_pslist *list, void (*pnt)(int))
{
    t_psnode *cur;

    if (!list || !list->pivot)
        return ;
    cur = list->pivot;
    pnt(cur->data);
    cur = cur->next;
    while (cur != list->pivot)
    {
        pnt(cur->data);
        cur = cur->next;
    }
}

void pslist_tail_print(t_pslist *list, void (*pnt)(int))
{
    t_psnode *cur;

    if (!list || !list->pivot)
        return ;
    cur = list->pivot->prev;
    pnt(cur->data);
    cur = cur->prev;
    while (cur != list->pivot->prev)
    {
        pnt(cur->data);
        cur = cur->prev;
    }
}

void    pslist_destroy(t_pslist **list, int keep_pool)
{
    if (!list || !*list)
        return ;
    if ((*list)->pool->pool_start && !keep_pool)
        mpool_destroy(&((*list)->pool));
    free(*list);
    *list = NULL;
}
