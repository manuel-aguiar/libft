/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:13:03 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 16:13:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memfunc.h"

void	ft_free_set_null(void *ptr)
{
	t_uchar **to_free;
    to_free = (unsigned char **)ptr;
    free(*to_free);
    *to_free = NULL;
}

void	ft_free_charmat(char **table, void(*del)(char *))
{
	int		i;

	if (!table)
		return ;
	i = 0;
	while (table[i])
	{
		del(table[i]);
		table[i] = NULL;
		i++;
	}
	ft_free_set_null(&table);
}

void	ft_free_charmat_null(char ***table, void(*del)(char *))
{
	int		i;
	char	**split;

	if (!table || !*table)
		return ;
	split = *table;
	i = 0;
	while (split[i])
	{
		del(split[i]);
		split[i] = NULL;
		i++;
	}
	ft_free_set_null(table);
}

void	ft_free_sizemat(void **table, size_t size, void(*del)(void *))
{
	size_t		i;
	t_uchar		**split;

	if (!table)
		return ;
	split = (t_uchar **)table;
	i = 0;
	while (i < size)
	{
		del(split[i]);
		split[i] = NULL;
		i++;
	}
	ft_free_set_null(&split);
}

void	ft_free_sizemat_null(void ***table, size_t size, void(*del)(void *))
{
	size_t		i;
	t_uchar		**split;

	if (!table || !*table)
		return ;
	split = *((t_uchar ***)table);
	i = 0;
	while (i < size)
	{
		del(split[i]);
		split[i] = NULL;
		i++;
	}
	ft_free_set_null(table);
}
