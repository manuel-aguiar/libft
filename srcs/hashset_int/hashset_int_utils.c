/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashset_int_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:54:22 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 15:54:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashset_int.h"

void	ihs_table_print(t_ihs_table *table, void (*pnt)(int))
{
    int	i;
    int	size;

    if (!table || !pnt)
        return ;
    if (table->zero)
        pnt(0);
    i = 0;
    size = table->size;
    while (i < size)
    {
        if (table->data[i])
            pnt(table->data[i]);
        if (table->collision[i])
            ismlist_head_print(table->collision[i], pnt);
        i++;
    }
}

void	ihs_free_table(t_ihs_table **table)
{
    int			i;
	t_ihs_table	*destroy;

    if (!table)
	{
        return ;
	}
	destroy = *table;
    i = 0;
    while (i < destroy->size)
    {
        if (destroy->collision[i])
            ismlist_destroy(&(destroy->collision[i]));
        i++;
    }
    free(destroy->data);
    free(destroy->collision);
    free(destroy);
	*table = NULL;
}
