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
# include "memory_pool.h"

# include <stdlib.h>
# include <stdint.h>

#include <stdio.h>

/* pushswap list is a circular doubly linekd list with a memory pool
all functions i ahve on libft apply except the structs and initializers will
be different

list min and max will be set to -1 upon initialization as we will use only
number 0 and above"

*/

typedef struct s_psnode
{
    int					data;
    struct s_psnode	*next;
    struct s_psnode	*prev;
} t_psnode;

typedef struct s_pslist
{
    t_psnode	*pivot;
    t_mpool		*pool;
    int			len;
	int			min;
	int			max;
} t_pslist;

t_pslist	*pslist_new(int elements, t_mpool *shared_pool);
void		pslist_in_head(t_pslist* list, int data);
void		pslist_in_tail(t_pslist* list, int data);
void		pslist_del_head(t_pslist* list);
void		pslist_del_tail(t_pslist* list);
void		pslist_head_print(t_pslist *list, void (*pnt)(int));
void		pslist_tail_print(t_pslist *list, void (*pnt)(int));
void		pslist_destroy(t_pslist **list, int keep_pool);


/* ps_preprocess.c*/
int		ps_preprocess(int **res, int ac, char **av);

/* ps_normalize.c*/
int		ps_normalize(int **arr, int size);

/* ps_arr_to_cdlist.c*/
int		ps_arr_to_cdlist(t_pslist **list, int **arr, int size);

/* ps_plays.c*/
void	pslist_swap_top(t_pslist *list, char *print);
void	pslist_push_top(t_pslist *to, t_pslist *from, char *print);
int		pslist_rotate_multi(t_pslist *list, int rotate, char *print);
void    pslist_rotate(t_pslist *list, int rotate, char *print);

/* ps_printlists.c*/
void	ps_printlists(t_pslist *a_list, t_pslist *b_list, void (*pnt)(int));
void	printmembs(int num);

/* minmax functions to update the list as numbers move*/

void minmax_add(t_pslist *list, int data);
void minmax_del(t_pslist *list, int data);


/* algos */

void 	ps_bubble_sort(t_pslist *list);

void	ps_merge_swap(t_pslist *a_list, t_pslist *blist);

void ps_split_list(t_pslist *alist, t_pslist *blist);


#endif
