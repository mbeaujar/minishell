NAME=minishell
NAME_TEST=test
CC=clang
RM=rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE= -Llibft -lft
SRCS_DIRECTORY=source/
OBJS_DIRECTORY=objects/
SRCS =  prompt.c \
	main.c \
	env_create.c \
	env_linked_list.c \
	env_parsing.c \
	test.c

OBJ = ${SRCS:.c=.o}

OBJ_TEST = $(addprefix $(OBJS_DIRECTORY),$(OBJ))

OBJS = $(addprefix $(OBJS_DIRECTORY), $(filter-out test.o,$(OBJ)))

OBJS_TEST = $(filter-out $(OBJS_DIRECTORY)main.o,$(OBJ_TEST))

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CLFAGS) $(OBJS) $(INCLUDE) -o $(NAME)

test : $(OBJS_TEST)
	@$(CC) $(OBJS_TEST) $(INCLUDE) -lcriterion -o $(NAME_TEST)

clean : 
	@$(RM) $(NAME)
	@$(RM) $(NAME_TEST)
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_TEST)

fclean : clean
#	@make fclean -C libft

re : fclean all
