NAME=minishell
NAME_TEST=test
CC=clang
RM=rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE= -Llibft -lft
SRCS_DIRECTORY=source/
HEADER=include
OBJS_DIRECTORY=objects/
SRCS =  prompt/arrow.c \
		prompt/buffer.c \
		prompt/ctrl-key.c \
		prompt/display.c \
		prompt/key.c \
		prompt/linked_list.c \
		prompt/prompt.c \
		prompt/termcaps.c \
		prompt/termios.c 

OBJ = ${SRCS:.c=.o}

OBJ_TEST = $(addprefix $(OBJS_DIRECTORY),$(OBJ))

OBJS = $(addprefix $(OBJS_DIRECTORY), $(filter-out test.o,$(OBJ)))

OBJS_TEST = $(filter-out $(OBJS_DIRECTORY)main.o,$(OBJ_TEST))

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c
	@$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CLFAGS) $(OBJS) -lncurses $(INCLUDE) -o $(NAME)

test : $(OBJS_TEST)
	@$(CC) $(OBJS_TEST) -lcriterion -lncurses $(INCLUDE) -o $(NAME_TEST)

# --verbose

clean : 
	@$(RM) $(NAME)
	@$(RM) $(NAME_TEST)

fclean : clean
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_TEST)
#	@make fclean -C libft

re : fclean all
