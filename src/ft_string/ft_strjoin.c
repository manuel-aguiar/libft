/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:36:18 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 14:36:18 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new = malloc(sizeof(*new) * (len_s1 + len_s2 + 1));
	if (new)
	{
		ft_memcpy(new, s1, len_s1);
		ft_memcpy(&new[len_s1], s2, len_s2);
		new[len_s1 + len_s2] = '\0';
	}
	return (new);
}
