/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_int_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:49:02 by marvin            #+#    #+#             */
/*   Updated: 2023/05/02 10:49:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int ps_valid_char(char c)
{
	if (ft_isspace(c) || ft_isdigit(c) || c == '+' || c == '-')
		return (1);
	return (0);
}

static int	wordnum(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (str[i] && !ft_isspace(str[i]))
		count++;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (!ps_valid_char(str[i]))

			return (-1);

		i++;
	}
	while (str[i])
	{
		if (!ft_isspace(str[i]) && ft_isspace(str[i - 1]))
			count++;
		if (!ps_valid_char(str[i]))


			return (-1);

		i++;
	}
	return (count);
}

static int ps_atoi_overf(int res, char next, int *sign)
{
    int	max;

    max = INT_MAX / 10;
    if (res < max)
        return (1);
    if (res > max)
    {
        *sign = 0;
        return (0);
    }
    else if (res == max)
    {
        if (*sign == 1 && next > INT_MAX % 10 + '0')
        {
            *sign = 0;
            return (0);
        }
        if (*sign == -1 && next > -(INT_MIN % 10) + '0')
        {
            *sign = 0;
            return (0);
        }
    }
    return (1);
}

static int	ps_atoiable(char **arg, int *placenum)
{
    int		res;
    int		sign;
	char	*str;

	str = *arg;
    while (*str && ft_isspace(*str))
        str++;
    sign = 1;
    if (*str && *str == '-')
        sign = -1;
    if (*str && (*str == '-' || *str == '+'))
        str++;
    if (!ft_isdigit(*str))
        sign = 0;
    res = 0;
    while(*str && ft_isdigit(*str) && ps_atoi_overf(res, *str, &sign))
        res = res * 10 - '0' + *str++;
    *placenum = res * sign;
    if (sign == 0 || (!ft_isspace(*str) && *str))
        return (0);
	*arg = str;
    return (1);
}

int		split_to_list(char *arg, t_ihs_table *table, t_idmlist **placelist)
{
	t_idmlist	*new_list;
	int			total_nums;
	int			i;
	int			num;

	if (!arg || (total_nums = wordnum(arg)) == -1)
		return (-1);
	new_list = idmlist_new();
	if (new_list)
	{
		i = 0;
		while (i < total_nums)
		{
			if(ps_atoiable(&arg, &num) && ihs_insert(table, num))
				idmlist_in_tail(new_list, num);
			else
				return (-1);
			i++;
		}
	}
	else
		return (-1);
	*placelist = new_list;
	return (total_nums);
}

