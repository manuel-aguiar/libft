/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:44:07 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:44:07 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H


# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>


/* library sub-headers */
# include "memory_pool.h"
# include "ft_atoi.h"
# include "ft_memfunc.h"
# include "ft_string.h"
# include "ft_output.h"
# include "hashset_int.h"
# include "int_cd_list.h"
# include "int_dl_list.h"
# include "int_sl_list.h"
# include "int_xor_list.h"


/* memory_pool.h functions
files:
	- memory_pool.c
	- memory_pool_utils.c
*/
t_mpool	*mpool_create(size_t block_size, t_uint block_num);
void	mpool_destroy(t_mpool **pool);
void	*mpool_alloc(t_mpool *pool);
void	mpool_dealloc(t_mpool *pool, void* p);

/* PART 1*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(t_cchar *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, t_cchar *src, size_t size);
size_t	ft_strlcat(char *dst, t_cchar *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(t_cchar *s, int c);
char	*ft_strrchr(t_cchar *s, int c);
int		ft_strncmp(t_cchar *s1, t_cchar *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(t_cchar *big, t_cchar *little, size_t len);
int		ft_atoi(t_cchar *nptr);
void	*ft_calloc(size_t nmemb, size_t bytes);
char	*ft_strdup(t_cchar *s);

/*PART 2*/
char	*ft_substr(t_cchar *s, unsigned int start, size_t len);
char	*ft_strjoin(t_cchar *s1, t_cchar *s2);
char	*ft_strtrim(t_cchar *s1, t_cchar *set);
char	**ft_split(t_cchar *s, char c);
char	*ft_itoa(int nb);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int nb, int fd);

/*BONUS*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
