NAME = libft.a
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
INC = inc
ARC = ar rcs 
SRCS = ft_is/ft_isalnum.c \
       ft_is/ft_isalpha.c \
       ft_is/ft_isascii.c \
       ft_is/ft_isdigit.c \
       ft_is/ft_isprint.c \
       ft_lst/ft_lstadd_back.c \
       ft_lst/ft_lstadd_front.c \
       ft_lst/ft_lstclear.c \
       ft_lst/ft_lstdelone.c \
       ft_lst/ft_lstiter.c \
       ft_lst/ft_lstlast.c \
       ft_lst/ft_lstmap.c \
       ft_lst/ft_lstnew.c \
       ft_lst/ft_lstsize.c \
       ft_mem/ft_memccpy.c \
       ft_mem/ft_memchr.c \
       ft_mem/ft_memcmp.c \
       ft_mem/ft_memcpy.c \
       ft_mem/ft_memmove.c \
       ft_mem/ft_memset.c \
       ft_put/ft_putchar_fd.c \
       ft_put/ft_putendl_fd.c \
       ft_put/ft_putnbr_fd.c \
       ft_put/ft_putstr_fd.c \
       ft_str/ft_atoi.c \
       ft_str/ft_bzero.c \
       ft_str/ft_calloc.c \
       ft_str/ft_itoa.c \
       ft_str/ft_split.c \
       ft_str/ft_strchr.c \
       ft_str/ft_strdup.c \
       ft_str/ft_strjoin.c \
       ft_str/ft_strlcat.c \
       ft_str/ft_strlcpy.c \
       ft_str/ft_strlen.c \
       ft_str/ft_strmapi.c \
       ft_str/ft_strncmp.c \
       ft_str/ft_strnstr.c \
       ft_str/ft_strrchr.c \
       ft_str/ft_strtrim.c \
       ft_str/ft_substr.c \
       ft_to/ft_tolower.c \
       ft_to/ft_toupper.c \
       gnl/get_next_line.c \
       gnl/get_next_line_utils.c \
       printf/ft_count_len.c \
       printf/ft_fill_flags.c \
       printf/ft_print_address.c \
       printf/ft_print_char.c \
       printf/ft_print_hex.c \
       printf/ft_print_nbr.c \
       printf/ft_print_percent.c \
       printf/ft_print_put.c \
       printf/ft_print_string.c \
       printf/ft_printf.c \
       printf/ft_set_flags.c 

OBJS = $(SRCS:.c=.o)
_BLUE=\033[1;34m
_GREEN=\033[92m
_NC=\033[0m
all:    $(NAME)

$(NAME): $(OBJS)
	@echo "$(_BLUE)files .o created.$(NC)"
	@echo "$(_GREEN)$(NAME) created.$(NC)"
	@$(ARC) $(NAME) $(OBJS)

%.o:%.c $(INC)
	@$(CC) $(CFLAGS) -I$(INC) -o $@ -c $<

clean:
	@echo "$(_BLUE)files .o remove.$(NC)"
	@rm -f $(OBJS) $(B_OBJS)

fclean: clean
	@echo "$(_GREEN)$(NAME) remove.$(NC)"
	@rm -f $(NAME) $(B_NAME)

re: fclean all 

.PHONY: clean fclean all re $(NAME)

