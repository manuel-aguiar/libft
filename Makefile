FILES = 	ft_isalpha ft_isdigit ft_isalnum ft_isascii				\
			ft_isprint ft_strlen ft_memset ft_bzero					\
			ft_memcpy ft_memmove ft_strlcpy ft_strlcat				\
			ft_toupper ft_tolower ft_strchr ft_strrchr				\
			ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc					\
			ft_strdup ft_substr ft_strjoin ft_strtrim				\
			ft_split ft_itoa ft_strmapi ft_striteri					\
			ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd

B_FILES =	ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast			\
			ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter		\
			ft_lstmap
		 
HEADERS = *libft.h

NAME = libft.a


SRCS = $(addsuffix .c, $(FILES))
OBJS = ${SRCS:c=o}



B_SRCS = $(addsuffix .c, $(B_FILES))
B_OBJS = ${B_SRCS:c=o}


CC = cc
FLAGS = -c -Wall -Wextra -Werror
LIB = ar rcs
RM = rm -f
	
all: $(NAME)
	
$(NAME): $(OBJS)
	$(LIB) $@ $(OBJS)

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(FLAGS) -I$(HEADERS) $(SRCS)

$(B_OBJS): $(B_SRCS) $(HEADERS)
	$(CC) $(FLAGS) -I$(HEADERS) $(B_SRCS) 

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)

bonus: $(NAME) $(B_OBJS)
	$(LIB) $(NAME) $(B_OBJS)

re: fclean all

mkclean: all clean

.PHONY: clean fclean re mkclean