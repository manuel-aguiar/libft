#ifndef FT_OUTPUT_H

# define FT_OUTPUT_H

# include <unistd.h>

# include "ft_string.h"

/* to print to standard output*/

void	ft_putchar(char c);
void	ft_putendl(char *str);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);

/* to print to target fd*/
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *str, int fd);

#endif
