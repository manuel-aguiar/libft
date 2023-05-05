/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_list_malloc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:01 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:45:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "void_dl_list.h"

int vdmlist_find(t_vdmlist *list, void *data, int (*cmp)(void *, void *))
{
    t_vdmnode *cur;

    if (!list || !(list->head) || !cmp)
        return (0);
    cur = list->head;
    while (cur)
    {
        if (!cmp(cur->data, data))
            return (1);
        cur = cur->next;
    }
    return (0);
}

void vdmlist_remove_if(t_vdmlist *list, void *data, int (*cmp)(void *, void *), void(*del)(void *))
{
    t_vdmnode *cur;
    t_vdmnode *next;

    if (!list || !list->head)
        return ;
    cur = list->head;
    while (cur)
    {
        next = cur->next;
        if (!cmp(cur->data, data))
        {
            if (cur->prev)
                cur->prev->next = cur->next;
            else
            {
                list->head = cur->next;
                cur->next->prev = NULL;
            }
            if (cur->next)
                cur->next->prev = cur->prev;
            else
            {
                list->tail = cur->prev;
                cur->prev->next = NULL;
            }
			if (del)
				del(cur->data);
            free(cur);
		--(list->len);
        }
        cur = next;
    }
}


void vdmlist_del_head(t_vdmlist* list, void(*del)(void *))
{
    t_vdmnode *cur;

    if (!list || !(list->head))
        return ;
    cur = list->head;
    if (cur->next)
        cur->next->prev = NULL;
    else
        list->tail = NULL;
    list->head = cur->next;
	if (del)
		del(cur->data);
    free(cur);
    --(list->len);
}

void vdmlist_del_tail(t_vdmlist* list, void(*del)(void *))
{
    t_vdmnode *cur;

    if (!list || !(list->tail))
        return ;
    cur = list->tail;
    if (cur->prev)
        cur->prev->next = NULL;
    else
        list->head = NULL;
    list->tail = cur->prev;
	if (del)
		del(cur->data);
    free(cur);
    --(list->len);
}

void vdmlist_head_print(t_vdmlist *list, void (*pnt)(void *))
{
    t_vdmnode *cur;

    if (!list)
        return ;
    cur = list->head;
    while (cur)
    {
        pnt(cur->data);
        cur = cur->next;
    }
}

void vdmlist_tail_print(t_vdmlist *list, void (*pnt)(void *))
{
    t_vdmnode *cur;

    if (!list)
        return ;
    cur = list->tail;
    while (cur)
    {
        pnt(cur->data);
        cur = cur->prev;
    }
}

void    vdmlist_destroy(t_vdmlist **list, void(*del)(void *))
{
	t_vdmnode *delete;
	t_vdmnode *next;

    if (!list || !*list)
        return ;
    delete = (*list)->head;
	while (delete)
	{
		next = delete->next;
		if (del)
			del(delete->data);
		free(delete);
		delete = next;
	}
    free(*list);
    *list = NULL;
}
