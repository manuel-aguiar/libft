#include "int_sl_list.h"

t_ismnode *ismnode_new(int nbr)
{
    t_ismnode *new;

    new = malloc(sizeof(*new));
    if (!new)
        return (NULL);
    new->data = nbr;
    new->next = NULL;
    return (new);
}

t_ismlist *ismlist_new(void)
{
    t_ismlist *list;

    list = malloc(sizeof(*list));
    if (!list)
        return (NULL);
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return (list);
}

void ismlist_in_head(t_ismlist* list, int data)
{
    t_ismnode* new_node;

    if (!list)
        return ;
    new_node = ismnode_new(data);
    if (!new_node)
        return ;
    if (list->head)
        new_node->next = list->head;
    else
        list->tail = new_node;
    list->head = new_node;
    ++(list->len);
}

void ismlist_in_tail(t_ismlist* list, int data)
{
    t_ismnode* new_node;

    if (!list)
        return ;
    new_node = ismnode_new(data);
    if (!new_node)
        return ;
    if (list->tail)
        list->tail->next = new_node;
    else
        list->head = new_node;
    list->tail = new_node;
    ++(list->len);
}
