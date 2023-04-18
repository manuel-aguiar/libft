/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_list_malloc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:39:23 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 15:59:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sl_list.h"
#include "ft_output.h"

int ismlist_find(t_ismlist *list, int target)
{
    t_ismnode *cur;

    if (!list || !(list->head))
        return (0);
    cur = list->head;
    while (cur)
    {
        if (cur->data == target)
            return (1);
        cur = cur->next;
    }
    return (0);
}

void    ismlist_removeif(t_ismlist *list, int target)
{
    t_ismnode *cur;
    t_ismnode dummy;
    t_ismnode *delete;

    if (!list || !list->head)
        return ;
    list->tail = &dummy;
    cur = list->head;
    while(cur)
    {
        if (cur->data == target)
        {
            delete = cur;
            cur = cur->next;
            free(delete);
            --(list->len);
        }
        else
        {
            list->tail->next = cur;
            cur = cur->next;
            list->tail = list->tail->next;
        }
    }
    list->tail->next = NULL;
    list->head = (dummy.next);
}


void ismlist_del_head(t_ismlist* list)
{
    t_ismnode *cur;

    if (!list || !(list->head))
        return ;
    cur = list->head;
    if (!cur->next)
        list->tail = NULL;
    list->head = cur->next;
    free(cur);
    --(list->len);
}

void ismlist_head_print(t_ismlist *list, void (*pnt)(int))
{
    t_ismnode *cur;

    if (!list)
        return ;
    cur = list->head;
    while (cur)
    {
        pnt(cur->data);
        cur = cur->next;
    }
}

void    ismlist_destroy(t_ismlist **list)
{
	t_ismnode *del;
	t_ismnode *next;

    if (!list || !*list)
        return ;
    del = (*list)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
    free(*list);
    *list = NULL;
}
