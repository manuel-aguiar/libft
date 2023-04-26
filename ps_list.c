/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_list_mpool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:51:43 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:51:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_psnode *new_psnode(int nbr, t_mpool *pool)
{
    t_psnode *new;

    if (!pool || !pool->pool_start)
        return (NULL);
    new = (t_psnode *)mpool_alloc(pool);
    if (!new)
        return (NULL);
    new->data = nbr;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_pslist *pslist_new(int elements, t_mpool *shared_pool)
{
    t_pslist *list;
    t_mpool *pool;

    list = malloc(sizeof(*list));
    if (!list)
        return (NULL);
    if (!shared_pool || shared_pool->block_size != sizeof(t_psnode))
    {
        pool = mpool_create(sizeof(t_psnode), elements);
        if (!pool)
        {
            free(list);
            return (NULL);
        }
    }
    else
        pool = shared_pool;
    list->pivot = NULL;
    list->pool = pool;
    list->len = 0;
    return (list);
}

void pslist_in_head(t_pslist* list, int data)
{
    pslist_in_tail(list, data);
    list->pivot = list->pivot->prev;
}

void pslist_in_tail(t_pslist* list, int data)
{
    t_psnode* new_node;

    if (!list)
        return ;
    new_node = new_psnode(data, list->pool);
    if (!new_node)
        return ;
    if (list->pivot)
    {
        new_node->next = list->pivot;
        new_node->prev = list->pivot->prev;
        new_node->prev->next = new_node;
        new_node->next->prev = new_node;
    }
    else
    {
        new_node->next = new_node;
        new_node->prev = new_node;
        list->pivot = new_node;
    }
    ++(list->len);
}
