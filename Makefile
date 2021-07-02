UNAME=$(shell uname)

ifeq ($(UNAME), Darwin)
	LIBFT=ftmacos
endif
ifeq ($(UNAME), Linux)
	LIBFT=ftlinux
endif

NAME=minishell
NAME_TEST=test
CC=clang
RM=rm -f
CFLAGS = -Wall -Wextra -Werror -g
SRCS_DIRECTORY=source/
HEADER=include
PATH_LIB=libft/
FILE_LIB= $(addprefix $(PATH_LIB), lib$(LIBFT).a)
OBJS_DIRECTORY=objects/

SRCS =  main.c \
		cmd.c \
		builtin/cd.c \
		builtin/unset.c \
		builtin/pwd.c \
		builtin/env.c \
		builtin/export.c \
		builtin/exit.c \
		builtin/echo.c \
		prompt/setup.c \
		prompt/ctrl-arrow.c \
		prompt/arrow.c \
		prompt/buffer.c \
		prompt/ctrl-key.c \
		prompt/display.c \
		prompt/key.c \
		prompt/move.c \
		prompt/linked_list.c \
		prompt/prompt.c \
		prompt/cut.c \
		prompt/copy_paste.c \
		prompt/termcaps.c \
		prompt/termios.c \
		prompt/prompt_non_tty.c \
		env/gestion.c \
		env/linked_list.c \
		env/split.c \
		env/create.c \
		env/shlvl.c \
		env/path.c \
		utils/ft_create_env.c \
		utils/ft_realloc.c \
		utils/ft_strjoin_env.c \
		utils/ft_strlen_tab.c \
		utils/ft_printtab.c \
		utils/ft_strcmp.c \
		utils/search_min.c \
		utils/ft_argv_strjoin.c \
		utils/ft_unleak_strjoin.c \
		utils/ft_secure_strdup.c \
		utils/ft_strfrom_tab.c \
		utils/export.c \
		lexer/lexer.c \
		lexer/linked_list.c \
		lexer/lexer_utils.c \
		lexer/lexer_char.c \
		lexer/count_char.c \
		lexer/search_type.c \
		parser/parser.c \
		parser/linked_list.c \
		parser/interpreter.c \
		parser/redir.c \
		parser/command.c \
		parser/variables.c \
		parser/cmd_utils.c \
		parser/unbuiltin.c \
		parser/child.c \
		parser/return.c 

SRCS_TEST = Criterion/tester/lexer.c \
			Criterion/tester/parser.c \
			Criterion/tester/prompt.c

OBJ = ${SRCS:.c=.o}

OBJECTS = objects/builtin \
		objects/env \
		objects/lexer \
		objects/parser \
		objects/prompt \
		objects/utils

OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJ))

OBJS_TEST = $(filter-out $(OBJS_DIRECTORY)main.o,$(OBJS))

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c
	@$(CC) $(CFLAGS) $< -I$(HEADER) -c -o $@

all : $(FILE_LIB) $(OBJECTS) $(NAME)

$(OBJECTS) : 
	@mkdir -p objects $(OBJECTS)

$(FILE_LIB) : 
ifeq ("$(wildcard $(FILE_LIB))","")
	@make re -C $(PATH_LIB)
endif

$(NAME) : $(OBJS)
	@$(CC) $(CLFAGS) $(OBJS) -lncurses -L$(PATH_LIB) -l$(LIBFT) -o $(NAME)

action : fclean test


test : $(FILE_LIB) $(OBJECTS) $(OBJS)
	@$(CC) $(OBJS_TEST) $(SRCS_TEST) -I$(HEADER) -lcriterion -lncurses -L$(PATH_LIB) -l$(LIBFT) -o $(NAME_TEST)

tester: re
	@sh Criterion/build.sh

clean : 
	@$(RM) $(NAME)
	@$(RM) $(NAME_TEST)

bonus : 
	git add -A
	git commit -m "update bonus"
	git push -u origin bonus

fclean : clean
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_TEST)
#	@make fclean -C libft

clear : 
ifeq ("$(wildcard $(FILE_LIB))","$(FILE_LIB)")
	@make fclean -C $(PATH_LIB)
endif

re : fclean all
