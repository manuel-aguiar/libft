/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:01:24 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:01:24 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*move;
	unsigned char	cc;

	cc = (unsigned char)c;
	move = s + ft_strlen(s);
	while (move > s && *move != cc)
		move--;
	if (*move == cc)
		return ((char *)move);
	return (NULL);
}
