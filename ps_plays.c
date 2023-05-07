/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_playssss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:02:56 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 16:02:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int		   pslist_swap_top(t_ps_stack *stack, int options)
{
    t_icplist *list;
	t_icpnode *old_top;
    t_icpnode *new_top;

	list = stack->list;
    if (!list || list->len <= 1)
        return (0);
    list->pivot = list->pivot->next;
    if (stack->list->len > 1)
    {
        old_top = list->pivot->prev;
        new_top = list->pivot;
        old_top->next = new_top->next;
        new_top->next->prev = old_top;
        new_top->prev = old_top->prev;
        old_top->prev->next = new_top;
        old_top->prev = new_top;
        new_top->next = old_top;
    }
	if (options & O_PRINT && !stack->trial_mode && !(options & O_COMBO))
		ft_printf("%s", stack->swap_name);
	if (options & O_COUNT && !stack->trial_mode && !(options & O_COMBO))
		(stack->op_counter)++;
	if (options & O_SAVE || (stack->trial_mode && (!(options & O_REVERSE))))
		save_command(stack, stack->swap_name);
	return (1);
}

static t_icpnode    *pslist_retrieve_top(t_ps_stack *stack)
{
    t_icplist *list;
	t_icpnode *ret;

	list = stack->list;
    if (!list || !(list->pivot))
        return (NULL);
    ret = list->pivot;
    if (list->len > 1)
    {
        list->pivot = list->pivot->next;
        ret->prev->next = ret->next;
        ret->next->prev = ret->prev;
    }
    else
        list->pivot = NULL;
    --(list->len);
    return (ret);
}

static int    pslist_add_top(t_ps_stack *stack, t_icpnode *newtop)
{
	t_icplist *list;

	list = stack->list;
    if (!list || !newtop)
        return (0);
    if (!(list->pivot))
    {
        newtop->next = newtop;
        newtop->prev = newtop;
    }
    else
    {
        newtop->next = list->pivot;
        newtop->prev = list->pivot->prev;
        newtop->prev->next = newtop;
        newtop->next->prev = newtop;
    }
    list->pivot = newtop;
    ++(list->len);
    return (1);
}


int    pslist_push_top(t_ps_stack *to, t_ps_stack *from, int options)
{
    t_icpnode *move;

    if (!to->list || !from->list || !from->list->pivot)
        return (0);
    move = pslist_retrieve_top(from);
    if (move)
        pslist_add_top(to, move);
	if (options & O_PRINT && !from->trial_mode && !(options & O_COMBO))
		ft_printf("%s", from->push_name);
	if (options & O_COUNT && !from->trial_mode && !(options & O_COMBO))
		(from->op_counter)++;
	if (options & O_SAVE || (from->trial_mode && (!(options & O_REVERSE))))
		save_command(from, from->push_name);
	return (1);
}

int    pslist_rotate(t_ps_stack *stack, int rotate, int options)
{
	t_icplist *list;

	if (rotate == 0)
		return (1);
	list = stack->list;
	if (rotate > 0)
		list->pivot = list->pivot->next;
	if (rotate < 0)

		list->pivot = list->pivot->prev;
	if (options & O_PRINT && !stack->trial_mode && !(options & O_COMBO))
	{
		if (rotate > 0)
			ft_printf("%s", stack->rotate_name);
		else
			ft_printf("%s", stack->revrot_name);
	}
	if (options & O_COUNT && !stack->trial_mode && !(options & O_COMBO))
		(stack->op_counter)++;
	if (options & O_SAVE || (stack->trial_mode && (!(options & O_REVERSE))))
	{
		if (rotate > 0)
			save_command(stack, stack->rotate_name);
		else
			save_command(stack, stack->revrot_name);
	}
	if (rotate > 0)
		rotate--;
	else
		rotate++;
	return (pslist_rotate(stack, rotate, options));
}

int save_command(t_ps_stack *stack, char *command)
{
	char *save;

	if (!stack->save_plays)
		stack->save_plays = vdmlist_new();
	if (!stack->save_plays)
		return (0);
	save = ft_strdup(command);
	if (!save)
		return (0);
	if(vdmlist_in_tail(stack->save_plays, save))
		return (1);
	return (0);
}
