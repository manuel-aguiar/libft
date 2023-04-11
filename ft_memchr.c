/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:20:38 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:20:38 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*move;
	unsigned char	cc;

	if (n == 0)
		return (NULL);
	cc = (unsigned char)c;
	move = (unsigned char *)s;
	while (--n && *move != cc)
		move++;
	if (*move == cc)
		return (move);
	return (NULL);
}
