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

# define MAGIC_SIZE 200
# define MAGIC_NORM 50
# define INSORT_TO_A 20
# define INSORT_TO_B INSORT_TO_A / 2


# include <stdio.h>

/* pushswap list is a circular doubly linekd list with a memory pool
all functions i ahve on libft apply except the structs and initializers will
be different

list min and max will be set to -1 upon initialization as we will use only
number 0 and above"

*/

/* ps_preprocess.c*/
int		ps_preprocess(int **res, int ac, char **av);

/* ps_normalize.c*/
int		ps_normalize(int **arr, int size);

/* ps_arr_to_cdlist.c*/
int		ps_arr_to_cdlist(t_icplist **list, int **arr, int size);

/* ps_plays.c*/
void	pslist_swap_top(t_icplist *list, char *print);
void	pslist_push_top(t_icplist *to, t_icplist *from, char *print);
int		pslist_rotate_multi(t_icplist *list, int rotate, char *print);
void    pslist_rotate(t_icplist *list, int rotate, char *print);

/* ps_printlists.c*/
void	ps_printlists(t_icplist *a_list, t_icplist *b_list, void (*pnt)(int));
void	printmembs(int num);

/* minmax functions to update the list as numbers move*/


/* algos */

void 	ps_bubble_sort(t_icplist *list);

void	ps_merge_swap(t_icplist *a_list, t_icplist *blist);

void ps_split_list(t_icplist *alist, t_icplist *blist, int ac);

void dumpable (t_icplist *alist, t_icplist *blist);

void	ps_merge_stacks(t_icplist *alist, t_icplist *blist, int prev_min);

int is_ordered(t_icplist *list);

int total_radix_ops(int size);
void	get_b_max_on_top(t_icplist *blist);
void 	find_b_place(t_icplist *blist, int target);
void pushbucket(t_icplist *alist, t_icplist *blist, int min, int max);
void dumpbucket(t_icplist *alist, t_icplist *blist, int start, int end);
void ps_buckets(t_icplist *alist, t_icplist *blist, int bucksize, int total);

void ps_buckets_to_a(t_icplist *alist, t_icplist *blist, int bucksize, int total);

void test_bench(t_icplist *alist, t_icplist *blist, int total);

#endif
