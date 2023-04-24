

#include "libft.h"

// gcc -Wall -Werror -Wextra srcs/**/*.c -Iincs
// gcc *.c -L. -lft -Iincs
#include <time.h>
#include <stdio.h>
/*
void	printmembs(int num)
{
	ft_printf("%d   ", num);
}

int ascending(int a, int b)
{
	return (a > b);
}


int ps_normalize(int **arr, int size);

int ps_preprocess(int **res, int ac, char **av);

int	ps_arr_to_cdlist(t_pslist **list, int **arr, int size);

int main(int ac, char **av)
{

    ac--;
	av++;

	int *arr;
	t_pslist *list;
	int times = 1;

	int size = ft_atoi_arr(&arr, ac, av);

	ft_print_arr(arr, ac, &printmembs);
	tim_sort(arr, ac, &ascending);


	clock_t c;
    c = clock();
    int d = 0;
    while (d < times)
    {

		if (ps_preprocess(&arr, ac, av))
		{
			if (ps_normalize(&arr, ac))
			{
				if (ps_arr_to_cdlist(&list, &arr, ac))
				{
					ft_printf("successsssss\n\n\n");
					//pslist_head_print(list, &printmembs);
					pslist_destroy(&list, 0);
				}
				else
					ft_printf("failed placing in list\n");
			}
			else
				ft_printf("failed normalization\n");
		}
		else
			ft_printf("failed preprocessing\n");
        d++;
    }
    c = clock() - c;
    double time_takennn = ((double)c)/CLOCKS_PER_SEC;
    printf("norm slow         took %f\n", time_takennn);


	//ft_print_arr(tester, ac, "  ", &ft_putnbr);
	//ft_putstr("  <- normalized slow\n");


    return (0);
}
*/
