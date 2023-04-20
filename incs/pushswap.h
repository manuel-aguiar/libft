/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:37:46 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 11:37:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H

# define PUSHSWAP_H

# include "libft.h"

/* ps_preprocess.c*/
int ps_preprocess(int **res, int ac, char **av);
int ps_normalize(int **arr, int size);
int	ps_arr_to_cdlist(t_icplist **list, int **arr, int size);

/* ps_plays.c*/
void    icplist_swap_top(t_icplist *list);
void    icplist_push_top(t_icplist *to, t_icplist *from);
int    icplist_rotate(t_icplist *list, int rotate);

#endif
