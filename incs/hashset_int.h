#ifndef HASHSET_INT_H

# define HASHSET_INT_H

# include <stdlib.h>

# include "int_sl_list.h"
# include "ft_memfunc.h"

#define SIGN(Value) ({ __auto_type _v = (Value); (_v < 0) * -1 + (_v > 0) * 1;})
#define ABS(Value) ({ __auto_type _v = (Value); _v * SIGN(_v);})

typedef struct s_ihs_table
{
	int			*data;
	int			size;
	int			zero;
	t_ismlist	**collision;
} t_ihs_table;

t_ihs_table	*ihs_init_table(int size);
int			ihs_hash_function(int key, int tab_size);
int			ihs_contains(t_ihs_table *table, int key);
int			ihs_insert(t_ihs_table *table, int key);
int			ihs_remove(t_ihs_table *table, int key);
void		ihs_free_table(t_ihs_table **table);

/* escrever uma função para printar a tabela*/

#endif
