#ifndef FT_MEMFUNC_H

# define FT_MEMFUNC_H

# include <stdlib.h>
# include <stddef.h>
# include <limits.h>

#if defined(__LP64__) || defined(_WIN64)
# define UL_SIZE 8
# define UL_ALIGN 7
#elif defined(__x86_64__) || defined(__aarch64__)
# define UL_SIZE 8
# define UL_ALIGN 7
#elif defined(__LP32__) || defined(_WIN32)
# define UL_SIZE 4
# define UL_ALIGN 3
#elif defined(__i386__) || defined(__arm__)
# define UL_SIZE 4
# define UL_ALIGN 3
#else
# define UL_SIZE 1
# define UL_ALIGN 0
#endif

#define FOUR_UNROLL 4
#define TWO_UNROLL 2

typedef unsigned long	t_ulong;
typedef unsigned char	t_uchar;
typedef const char		t_cchar;

void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_calloc(size_t nmemb, size_t bytes);

/*functions to free, ft_free_misc.c*/
void	ft_free_charmat(char **table, void(*del)(char *));
void	ft_free_charmat_null(char ***table, void(*del)(char *));
void	ft_free_sizemat(void **table, size_t size, void(*del)(void *));
void	ft_free_sizemat_null(void ***table, size_t size, void(*del)(void *));
void	ft_free_set_null(void *ptr);
#endif
