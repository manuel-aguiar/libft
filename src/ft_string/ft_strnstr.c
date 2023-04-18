/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:32:12 by manuel            #+#    #+#             */
/*   Updated: 2023/03/17 18:32:12 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lillen;

	if (!*little)
		return ((char *)big);
	lillen = ft_strlen((char *)little);
	i = 0;
	while (big[i] && i < len - lillen + 1)
	{
		if (big[i] == *little)
		{
			j = 0;
			while (big[i + j] == little[j] && little[j + 1] && i + j < len)
				j++;
			if (big[i + j] == little[j] && little[j + 1] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
