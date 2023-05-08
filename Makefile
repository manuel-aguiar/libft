
## PATH ##
INC_PATH		=	incs
SRC_PATH		=	srcs
OBJ_PATH		=	objs

ATOI			=	atoi
MEMFUNC 		=	ft_memfunc
OUTPUT			=	ft_output
PRINTF			=	ft_printf
STRING			=	ft_string
GNL				=	get_next_line
HASHINT			=	hashset_int
LICIRC			=	int_circular_list
LIDBL			=	int_doubly_list
LISNGL			=	int_single_list
LIXOR			=	int_xor_linkedlist
LVDBL			=	void_dl_list
ISORT			=	int_sorting
MATH			=	math
MPOOL			=	memory_pool

FILES_ATOI		=	ft_atoi_arr.c 				\
					ft_atoi_overf.c 			\
					ft_atoi.c					\
					ft_itoa.c

FILES_MEMFUNC	=	ft_bzero.c					\
					ft_calloc.c					\
					ft_free_misc.c				\
					ft_memchr.c					\
					ft_memcmp.c					\
					ft_memcpy.c					\
					ft_memmove.c				\
					ft_memset.c

FILES_OUTPUT	=	ft_print_arr.c				\
					ft_putchar_fd.c				\
					ft_putendl_fd.c				\
					ft_putnbr_fd.c				\
					ft_putstr_fd.c

FILES_PRINTF	=	ft_printf_csdiu_perc.c		\
					ft_printf_pxX.c				\
					ft_printf.c

FILES_STRING	=	ft_isalnum.c				\
					ft_isalpha.c				\
					ft_isascii.c				\
					ft_isdigit.c				\
					ft_isprint.c				\
					ft_isspace.c				\
					ft_split.c					\
					ft_strchr.c					\
					ft_strdup.c					\
					ft_striteri.c				\
					ft_strjoin.c				\
					ft_strlcat.c				\
					ft_strlcpy.c				\
					ft_strlen.c					\
					ft_strmapi.c				\
					ft_strncmp.c				\
					ft_strnstr.c				\
					ft_strrchr.c				\
					ft_strtrim.c				\
					ft_substr.c					\
					ft_tolower.c				\
					ft_toupper.c

FILES_GNL		=	get_next_line.c				\
					get_next_line_utils.c

FILES_HASHINT	=	hashset_int.c				\
					hashset_int_utils.c


FILES_LICIRC	=	cd_list_mpool.c				\
					cd_list_mpool_utils.c

FILES_LIDBL		=	dll_list_malloc.c			\
					dll_list_malloc_utils.c		\
					dll_list_mpool.c			\
					dll_list_mpool_utils.c

FILES_LISNGL	=	sl_list_malloc.c			\
					sl_list_malloc_utils.c

FILES_LIXOR		=	xor_list_malloc.c			\
					xor_list_malloc_utils.c		\
					xor_list_mpool.c			\
					xor_list_mpool_utils.c

FILES_LVDBL		=	vdlist_malloc.c				\
					vdlist_malloc_utils.c		\
					vdlist_mpool.c				\
					vdlist_mpool_utils.c

FILES_ISORT		=	cocktailsort.c				\
					mergesort.c					\
					quicksort.c					\
					tim_sort.c					\
					tim_sort_utils.c			\

FILES_MATH		=	bin_srch.c

FILES_MPOOL		=	memory_pool.c				\
					memory_pool_utils.c


NAME = libft.a
GCC = gcc
FLAGS = -c -Wall -Wextra -Werror
LIB = ar rcs
RM = rm


SRC_DIRS		=	$(ATOI)		$(MEMFUNC)	$(OUTPUT)	$(PRINTF) 	\
					$(STRING)	$(GNL)		$(HASHINT)	$(LICIRC)	\
					$(LIDBL)	$(LISNGL)	$(LIXOR)	$(LVDBL)	\
					$(ISORT)	$(MATH)		$(MPOOL)

SRCS = $(foreach src_dir,$(SRC_DIRS),$(wildcard $(SRC_PATH)/$(src_dir)/*.c))

OBJS = $(addprefix $(OBJ_PATH)/, $(notdir $(SRCS:.c=.o)))


all: $(NAME)

$(NAME): $(OBJS)
	$(LIB) $@ $(OBJS)

$(OBJS): $(SRCS) $(INC_PATH) | $(OBJ_PATH)
	$(GCC) $(FLAGS) -I$(INC_PATH) -o $(OBJ_PATH)/$(notdir $@) -c $<

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_PATH)
	rmdir $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

mkclean: all clean

bruh:
	rm mymain.exe

.PHONY: clean fclean re mkclean bruh
