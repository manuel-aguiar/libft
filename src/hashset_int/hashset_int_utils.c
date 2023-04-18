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

void iht_free_table(t_iht_table **table)
{
    int			i;
	t_iht_table	*destroy;

    if (!table)
        return ;
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
