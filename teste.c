#include "libft.h"

// gcc -Wall -Werror -Wextra srcs/**/*.c -Iincs
// gcc *.c -L. -lft -Iincs
#include <time.h>
#include <stdio.h>

void	printmembs(int num)
{
	ft_printf("%d   ", num);
}

int ps_normalize(int **arr, int size);

int ps_preprocess(int **res, int ac, char **av);

int	ps_arr_to_cdlist(t_icplist **list, int **arr, int size);

int main(int ac, char **av)
{

    ac--;
	av++;

	int *arr;
	t_icplist *list;
	int times = 1;



	clock_t c;
    c = clock();
    int d = 0;
    while (d < times)
    {
		ps_preprocess(&arr, ac, av);
		ps_normalize(&arr, ac);
		ps_arr_to_cdlist(&list, &arr, ac);
		//icplist_head_print(list, &printmembs);
		icplist_destroy(&list, 0);
        d++;
    }
    c = clock() - c;
    double time_takennn = ((double)c)/CLOCKS_PER_SEC;
    printf("norm slow         took %f\n", time_takennn);


	//ft_print_arr(tester, ac, "  ", &ft_putnbr);
	//ft_putstr("  <- normalized slow\n");


    return (0);
}
