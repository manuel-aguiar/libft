/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_playssss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:02:56 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 16:02:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void    pslist_swap_top(t_pslist *list, char *print)
{
    t_psnode *old_top;
    t_psnode *new_top;

    if (!list || list->len <= 1)
        return;
    list->pivot = list->pivot->next;
    if (list->len > 1)
    {
        old_top = list->pivot->prev;
        new_top = list->pivot;
        old_top->next = new_top->next;
        new_top->next->prev = old_top;
        new_top->prev = old_top->prev;
        old_top->prev->next = new_top;
        old_top->prev = new_top;
        new_top->next = old_top;
    }
	if (print)
		ft_printf("%s\n", print);
}

static t_psnode    *pslist_retrieve_top(t_pslist *list)
{
    t_psnode *ret;

    if (!list || !(list->pivot))
        return (NULL);
    ret = list->pivot;
    if (list->len > 1)
    {
        list->pivot = list->pivot->next;
        ret->prev->next = ret->next;
        ret->next->prev = ret->prev;
    }
    else
        list->pivot = NULL;
    --(list->len);
    return (ret);
}

static int    pslist_add_top(t_pslist *list, t_psnode *newtop)
{
    if (!list || !newtop)
        return (0);
    if (!(list->pivot))
    {
        newtop->next = newtop;
        newtop->prev = newtop;
    }
    else
    {
        newtop->next = list->pivot;
        newtop->prev = list->pivot->prev;
        newtop->prev->next = newtop;
        newtop->next->prev = newtop;
    }
    list->pivot = newtop;
    ++(list->len);
    return (1);
}


void    pslist_push_top(t_pslist *to, t_pslist *from, char *print)
{
    t_psnode *move;

    if (!to || !from || !from->pivot)
        return ;
    move = pslist_retrieve_top(from);
    if (move)
	{
        pslist_add_top(to, move);
	}
	if (print)
		ft_printf("%s\n", print);
}

int    pslist_rotate_multi(t_pslist *list, int rotate, char *print)
{
    t_psnode    *pivot;
    int     nbr;
    int     i;

    nbr = rotate % (list->len);
    if (!list || !nbr)
        return (nbr);
    if (ABS(nbr) > list->len / 2)
        nbr = (nbr - list->len * SIGN(nbr));
    pivot = list->pivot;
    i = nbr;
    while (i > 0)
    {
        pivot = pivot->next;
		ft_printf("%s\n", print);
        i--;
    }
    while (i < 0)
    {
        pivot = pivot->prev;
		ft_printf("%s\n", print);
        i++;
    }
    list->pivot = pivot;
    return (nbr);
}

void    pslist_rotate(t_pslist *list, int rotate, char *print)
{
	if (rotate == 1)
		list->pivot = list->pivot->next;
	if (rotate == -1)
		list->pivot = list->pivot->prev;
	if (print)
		ft_printf("%s\n", print);
}
