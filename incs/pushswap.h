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
# define TRUE 1
# define FALSE 0


#include <stdio.h>


typedef struct s_ps_stack
{
	t_icplist	*list;
	t_vdmlist 	*save_plays;
	char		push_name[4];
	char		swap_name[4];
	char		rotate_name[4];
	char		revrot_name[5];
	char		swap_combo[4];
	char		rotate_combo[4];
	char		revrot_combo[5];
	int			ascending;
	int			op_counter;
	int			trial_mode;
} t_ps_stack;

enum e_play_options
{
	O_PRINT = 1 << 0,
	O_COUNT = 1 << 1,
	O_SAVE = 1 << 2,
	O_REVERSE = 1 << 3,
	O_BUF = 1 << 4,
	O_COMBO = 1 << 5,
};

/* DELEEEEEEEETEEEEEEEEEEEEEEEEEEEEEE*/

/* pushswap list is a circular doubly linekd list with a memory pool
all functions i ahve on libft apply except the structs and initializers will
be different

list min and max will be set to -1 upon initialization as we will use only
number 0 and above"

*/

/* ps_preprocess.c*/
int		ps_preprocess(t_icplist **final, int ac, char **av);

/* ps_preprocess_utils.c*/

int		ps_valid_char(char c);
int		wordnum(char *str);
int		ps_atoi_overf(int res, char next, int *sign);
int		ps_atoiable(char **arg, int *placenum);


/* ps_normalize.c*/
int		ps_normalize(t_icplist **final);

/* ps_plays.c*/
int    pslist_swap_top(t_ps_stack *stack, int options);
int    pslist_push_top(t_ps_stack *to, t_ps_stack *from, int options);
int    pslist_rotate(t_ps_stack *stack, int rotate, int options);
int		save_command(t_ps_stack *stack, char *command);
int		delete_command(t_ps_stack *stack, char *command);


/* ps_list_utils.c*/
int		ps_arr_to_cdlist(t_icplist **list, int **arr, int size);
void	ps_printlists(t_icplist *a_list, t_icplist *b_list, void (*pnt)(int));
void	printmembs(int num);
int		is_sorted(t_ps_stack *a_stack, t_ps_stack *b_stack);

/* algos */

/*ps_sorting_pushswap.c*/
void	pushswap(t_ps_stack *a_stack, t_ps_stack *b_stack, int total);
void	quick_sort_a(t_ps_stack *a_stack, t_ps_stack *b_stack, int start, int end);
void	quick_sort_b(t_ps_stack *a_stack, t_ps_stack *b_stack, int start, int end);

/*ps_sorting_common.c*/
int		in_bucket(int target, int min, int max);
int		is_target(int target, int test);
int		find_exact_target(t_ps_stack *stack, int target);
int		find_closest_in_bucket(t_ps_stack *stack, int min, int max);
void	super_swap(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);

/*ps_quicksort_moves.c*/
void	pushbucket(t_ps_stack *from, t_ps_stack *to, int min, int max);
void	insertion_sort_push(t_ps_stack *to, t_ps_stack *from, int start, int end);
void 	put_target_to_top(t_ps_stack *stack, int target, int min, int max);

/*ps_sorting_small.c*/
void 	pushswap_sort_two(t_ps_stack *stack, int print);
void 	pushswap_sort_three(t_ps_stack *stack);
void	pushswap_sort_small(t_icplist *alist, t_icplist *blist, int min, int max);

/*ps_sorting_medium.c*/


/*ps_check_sort.c*/
int		bucket_is_sorted(t_ps_stack *stack, int min, int max);
int		bucket_is_sorted_debug(t_icplist *list, int min, int max, int ascending);
void	go_to_bucket_begins(t_ps_stack *stack, int min, int max, int options);

/*ps_messages.c - error messages and functions*/
int		ok_message(void);
int		ko_message(void);
int		error_msg(void);
int		malloc_failed(void);

/*ps_array_cocktail.c*/
int	ps_array_cocktail_counter(int *arr, int len);
int	ps_array_insertion_counter(int *arr, int len, int min, int max);


/* pushswap.c*/

void	setup_stack_a(t_ps_stack *a);
void	setup_stack_b(t_ps_stack *b);

void	stack_cocktail(t_ps_stack *stack, int min, int max, int options);

void pushswap_super_small(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);

int test_best_entry(t_ps_stack *stack);

/* ps_execute_ops.c*/
int		execute_single(t_ps_stack *stack, t_ps_stack *other, char *command, int options);
int		execute_combo(t_ps_stack *stack, t_ps_stack *other, char *command, int options);
char	*inst_reverse(t_ps_stack *stack, t_ps_stack *other, char *command);
int		execute_list_rev(t_ps_stack *a_stack, t_ps_stack *b_stack, t_vdmlist *ops, int options);
int		execute_list(t_ps_stack *a_stack, t_ps_stack *b_stack, t_vdmlist *ops, int options);



int trial(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);
void pushswap_double_ins(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);
void pushswap_double_cocktail(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);

#endif
