/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashset_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:35:34 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 15:35:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashset_int.h"

t_ihs_table	*ihs_init_table(int size)
{
    t_ihs_table	*table;
    t_ismlist	**collision;
    int			*array;

    table = malloc(sizeof(*table));
    if (!table)
        return (NULL);
    array = ft_calloc(sizeof(*array), size);
    table->data = array;
    table->size = size;
    table->zero = 0;
    collision = ft_calloc(sizeof(*collision), size);
	table->collision = collision;
    if (!collision || !array)
		ihs_free_table(&table);
    return (table);
}


int	ihs_hash_function(int key, int tab_size)
{
    return (ABS(key) % tab_size);
}

int	ihs_contains(t_ihs_table *table, int key)
{
    int index;

    if (!table)
        return (-1);
    if (key == 0)
    {
        if (!table->zero)
            return (0);
        return (1);
    }
    index = ihs_hash_function(key, table->size);
    if (table->data[index] == key)
        return (1);
    if (table->collision[index] && ismlist_find(table->collision[index], key))
        return (1);
    return (0);
}


int	ihs_insert(t_ihs_table *table, int key)
{
    int index;

    if (!table)
        return (-1);
    if (ihs_contains(table, key))
        return (0);
    if (key == 0)
    {
        table->zero = 1;
        return (1);
    }
    index = ihs_hash_function(key, table->size);
    if (!table->data[index])
        table->data[index] = key;
    else
    {
        if (!table->collision[index])
            table->collision[index] = ismlist_new();
        ismlist_in_head(table->collision[index], key);
    }
    return (1);
}

int	ihs_remove(t_ihs_table *table, int key)
{
    int index;

    if (!table)
        return (-1);
    if (!ihs_contains(table, key))
        return (0);
    if (key == 0)
    {
        table->zero = 0;
        return (1);
    }
    index = ihs_hash_function(key, table->size);
    if (table->data[index] == key)
        table->data[index] = 0;
    else
    {
        ismlist_removeif(table->collision[index], key);
        if (table->collision[index]->len == 0)
            ismlist_destroy(&(table->collision[index]));
    }
    return (1);
}

/*
#include <stdio>
void print_array(int *arr, int size);

#define TABLE_SIZE 20 // fixed size of hash table
int main() {

    t_ihs_table *table;

    table = ihs_init_table(TABLE_SIZE);

    ihs_insert(table, 40);
    ihs_insert(table, 20);
    ihs_insert(table, 60);

    print_array(table->data, TABLE_SIZE);

    printf("%d\n", ihs_contains(table, 20)); // output: 10
    printf("%d\n", ihs_contains(table, 0)); // output: 20
    printf("%d\n", ihs_contains(table, 40)); // output: 20
    printf("%d\n", ihs_contains(table, 60)); // output: 30
    ihs_remove(table, 20);
    printf("%d\n", ihs_contains(table, 20)); // output: -1
    ihs_free_table(table);
    return 0;
}
*/
