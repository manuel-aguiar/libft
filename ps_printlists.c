/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_printlists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:41:06 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 10:41:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ps_printlists(t_pslist *a_list, t_pslist *b_list, void (*pnt)(int))
{
	ft_printf("list B: ");
	pslist_head_print(b_list, pnt);
	ft_printf("\nlist A: ");
	pslist_head_print(a_list, pnt);
	ft_printf("\n");
}
