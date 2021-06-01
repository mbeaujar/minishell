UNAME=$(shell uname)

ifeq ($(UNAME), Darwin)
       NAME = libftmacos.a
endif
ifeq ($(UNAME), Linux)
       NAME = libftlinux.a
endif

CC = gcc 
CFLAGS = -Wall -Wextra -Werror
INC = inc
ARC = ar rcs 
SRCS = ft_put/ft_putchar_fd.c \
       ft_put/ft_putnbr_fd.c \
       ft_put/ft_putstr_fd.c \
       ft_str/ft_bzero.c \
       ft_str/ft_calloc.c \
       ft_str/ft_itoa.c \
       ft_str/ft_split.c \
       ft_str/ft_strchr.c \
       ft_str/ft_strdup.c \
       ft_str/ft_strjoin.c \
       ft_str/ft_strlen.c \
       ft_str/ft_strncmp.c \
       ft_str/ft_strnstr.c \
       ft_str/ft_strtrim.c \
       ft_str/ft_substr.c \
       gnl/get_next_line.c \
       gnl/get_next_line_utils.c 

OBJS = $(SRCS:.c=.o)
_BLUE=\033[0m
_GREEN=\033[0m
_NC=\033[0m
all:    $(NAME)

$(NAME): $(OBJS)
	@$(ARC) $(NAME) $(OBJS)

%.o:%.c $(INC)
	@$(CC) $(CFLAGS) -I$(INC) -o $@ -c $<

clean:
	@rm -f $(OBJS) $(B_OBJS)

fclean: clean
	@rm -f $(NAME) $(B_NAME)

re: fclean all 

.PHONY: clean fclean all re $(NAME)

