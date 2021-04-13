NAME=minishell
CC=clang
RM=rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
SRCS= source/prompt/main.c \
	source/utils/get_next_line_utils.c \
	source/utils/get_next_line.c \
	source/utils/ft_putstr.c \
	source/env/linked_list_env.c \
	source/env/create_env.c \
	source/env/parsing_env.c 

all : $(NAME)

$(NAME) : 
	@$(CC) $(CLFAGS) $(SRCS) -o $(NAME)

clean : 
	@$(RM) $(NAME)

fclean : clean

re : fclean all
