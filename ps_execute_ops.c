/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_execute_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:56:03 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/07 04:20:18 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"


int execute_combo(t_ps_stack *stack, t_ps_stack *other, char *command, int options)
{
    int found;

    //printf("checking combo\n");
    found = 0;
    if (!ft_strncmp(stack->swap_combo, command, ft_strlen(command)))
    {
        pslist_swap_top(stack, options | O_COMBO);
        pslist_swap_top(other, options | O_COMBO);
        found = 1;
    }
    else if (!ft_strncmp(stack->rotate_combo, command, ft_strlen(command)))
    {
        pslist_rotate(stack, 1, options | O_COMBO);
        pslist_rotate(other, 1, options | O_COMBO);
        found = 1;
    }
    else if (!ft_strncmp(stack->revrot_combo, command, ft_strlen(command)))
    {
        pslist_rotate(stack, -1, options | O_COMBO);
        pslist_rotate(other, -1, options | O_COMBO);
        found = 1;
    }
    if (found && options & O_PRINT)
        ft_printf("%s", command);
    return (found);
}

int execute_single(t_ps_stack *stack, t_ps_stack *other, char *command, int options)
{
    if (!ft_strncmp(stack->push_name, command, ft_strlen(command)))
        return (pslist_push_top(other, stack, options));
    if (!ft_strncmp(stack->swap_name, command, ft_strlen(command)))
        return (pslist_swap_top(stack, options));
    if (!ft_strncmp(stack->rotate_name, command, ft_strlen(command)))
        return (pslist_rotate(stack, 1, options));
    if (!ft_strncmp(stack->revrot_name, command, ft_strlen(command)))
        return (pslist_rotate(stack, -1, options));
    return (0);
}

char *inst_reverse(t_ps_stack *stack, t_ps_stack *other, char *command)
{
    if(!ft_strncmp(stack->push_name, command, ft_strlen(command)))
        return (other->push_name);
    if(!ft_strncmp(stack->swap_name, command, ft_strlen(command)))
        return (stack->swap_name);
    if(!ft_strncmp(stack->rotate_name, command, ft_strlen(command)))
        return (stack->revrot_name);
    if(!ft_strncmp(stack->revrot_name, command, ft_strlen(command)))
        return (stack->rotate_name);
    if(!ft_strncmp(other->push_name, command, ft_strlen(command)))
        return (stack->push_name);
    if(!ft_strncmp(other->swap_name, command, ft_strlen(command)))
        return (other->swap_name);
    if(!ft_strncmp(other->rotate_name, command, ft_strlen(command)))
        return (other->revrot_name);
    if(!ft_strncmp(other->revrot_name, command, ft_strlen(command)))
        return (other->rotate_name);
    if(!ft_strncmp(stack->swap_combo, command, ft_strlen(command)))
        return (stack->swap_combo);
    if(!ft_strncmp(stack->rotate_combo, command, ft_strlen(command)))
        return (stack->revrot_combo);
    if(!ft_strncmp(stack->revrot_combo, command, ft_strlen(command)))
        return (stack->rotate_combo);
    return (NULL);
}


int execute_list_rev(t_ps_stack *a_stack, t_ps_stack *b_stack, t_vdmlist *ops, int options)
{
    t_vdmnode *inst;
    char *reverse;

    inst = ops->tail;
    while (inst)
    {
        reverse = inst_reverse(a_stack, b_stack, inst->data);
        if (!execute_single(a_stack, b_stack, reverse, options) \
        && !execute_single(b_stack, a_stack, reverse, options) \
        && !execute_combo(a_stack, b_stack, reverse, options))
        {
            //printf("execucao de %s de merda, original era %s\n", reverse, (char *)inst->data);
            return (0);
        }
        //ps_printlists(a_stack->list, b_stack->list, &printmembs);
        //printf("execucao de %s bem sucedida original era %s\n", reverse, (char *)inst->data);
        inst = inst->prev;
    }
    return (1);
}

int	execute_list(t_ps_stack *a_stack, t_ps_stack *b_stack, t_vdmlist *ops, int options)
{
    t_vdmnode *inst;

    inst = ops->head;
    while (inst)
    {
        if (!execute_single(a_stack, b_stack, inst->data, options) \
        && !execute_single(b_stack, a_stack, inst->data, options) \
        && !execute_combo(a_stack, b_stack, inst->data, options))
            return (0);
        inst = inst->next;
    }
    return (1);
}

