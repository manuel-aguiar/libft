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
# define SORT_SMALL 30
# define INSORT_TO_A 20
# define INSORT_TO_B INSORT_TO_A / 2

#include <stdio.h>  //DELEEEEEEEEETE
/* GLOBAL VARIABLES TO DELETE*/

int counter;
int ss_counter;
int sa_counter;
int sb_counter;
/* DELEEEEEEEETEEEEEEEEEEEEEEEEEEEEEE*/

/* pushswap list is a circular doubly linekd list with a memory pool
all functions i ahve on libft apply except the structs and initializers will
be different

list min and max will be set to -1 upon initialization as we will use only
number 0 and above"

*/

/* ps_atoi_split.c*/
int		split_to_list(char *arg, t_ihs_table	*table, t_idmlist **placelist);


/* ps_preprocess.c*/
int		ps_preprocess(int **res, int ac, char **av, int *true_count);

/* ps_normalize.c*/
int		ps_normalize(int **arr, int size);

/* ps_plays.c*/
void	pslist_swap_top(t_icplist *list, char *print);
void	pslist_push_top(t_icplist *to, t_icplist *from, char *print);
int		pslist_rotate_multi(t_icplist *list, int rotate, char *print);
void	pslist_rotate(t_icplist *list, int rotate, char *print);

/* ps_list_utils.c*/
int		ps_arr_to_cdlist(t_icplist **list, int **arr, int size);
void	ps_printlists(t_icplist *a_list, t_icplist *b_list, void (*pnt)(int));
void	printmembs(int num);
int		is_sorted(t_icplist *alist, t_icplist *blist);

/* algos */

/*ps_sorting_pushswap.c*/
void	pushswap(t_icplist *alist, t_icplist *blist, int total);
void	quick_sort_a(t_icplist *alist, t_icplist *blist, int start, int end);
void	quick_sort_b(t_icplist *alist, t_icplist *blist, int start, int end);

/*ps_sorting_common.c*/
int		in_bucket(int target, int min, int max);
int		is_target(int target, int test);
int		find_exact_target(t_icplist *list, int target);
int		find_closest_in_bucket(t_icplist *list, int min, int max);
void	super_swap(t_icplist *alist, t_icplist *blist, int min, int max);

/*ps_sorting_a_stack.c*/
void	pushbucket_from_a(t_icplist *alist, t_icplist *blist, int min, int max);
void	insertion_sort_from_a(t_icplist *to, t_icplist *from, int start, int end);

/*ps_sorting_b_stack.c*/
void	pushbucket_from_b(t_icplist *alist, t_icplist *blist, int min, int max);
void	insertion_sort_from_b(t_icplist *to, t_icplist *from, int start, int end);

/*ps_sorting_small.c*/
void	pushswap_sort_three(t_icplist *list);
void	pushswap_sort_small(t_icplist *alist, t_icplist *blist, int min, int max);

/*ps_sorting_medium.c*/


/*ps_check_sort.c*/
int     bucket_is_sorted(t_icplist *list, int min, int max, int ascending);
int	bucket_is_sorted_debug(t_icplist *list, int min, int max, int ascending);

/*ps_messages.c - error messages and functions*/
int		ok_message(void);
int		ko_message(void);
int		error_msg(void);
int		malloc_failed(void);

/*ps_array_cocktail.c*/
int	ps_array_cocktail_counter(int *arr, int len);
int	ps_array_insertion_counter(int *arr, int len, int min, int max);


#endif
