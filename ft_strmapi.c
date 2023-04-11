/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:14:39 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:14:39 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	unsigned int		len;
	unsigned int		i;
	char				*new;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new = malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[len] = '\0';
	return (new);
}
