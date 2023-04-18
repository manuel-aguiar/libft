#ifndef HASHSET_INT_H

# define HASHSET_INT_H

# include <stdlib.h>

# include "int_sl_list.h"
# include "ft_memfunc.h"

#define SIGN(Value) ({ __auto_type _v = (Value); (_v < 0) * -1 + (_v > 0) * 1;})
#define ABS(Value) ({ __auto_type _v = (Value); _v * SIGN(_v);})

typedef struct s_iht_table
{
	int			*data;
	int			size;
	int			zero;
	t_ismlist	**collision;
} t_iht_table;

t_iht_table	*iht_init_table(int size);
int			iht_hash_function(int key, int tab_size);
int			iht_contains(t_iht_table *table, int key);
int			iht_insert(t_iht_table *table, int key);
int			iht_remove(t_iht_table *table, int key);
void		iht_free_table(t_iht_table **table);

/* escrever uma função para printar a tabela*/

#endif
