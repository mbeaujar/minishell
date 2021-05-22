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
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
SRCS_DIRECTORY=source/
HEADER=include
PATH_LIB=libft/
FILE_LIB= $(addprefix $(PATH_LIB), lib$(LIBFT).a)
#FILE_LIB=libft/libft.a
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
		prompt/arrow.c \
		prompt/buffer.c \
		prompt/ctrl-key.c \
		prompt/display.c \
		prompt/key.c \
		prompt/linked_list.c \
		prompt/prompt.c \
		prompt/termcaps.c \
		prompt/termios.c \
		env/gestion.c \
		env/linked_list.c \
		env/split.c \
		env/create.c \
		env/shlvl.c \
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
		lexer/count_char.c \
		lexer/search_type.c \
		parser/parser.c \
		parser/linked_list.c \
		parser/interpreter.c \
		parser/command.c \
		parser/variables.c \
		parser/pipe.c \
		parser/unbuiltin.c \
		parser/child.c \
		parser/pipe_utils.c 

SRCS_TEST = Criterion/tester/lexer.c \
			Criterion/tester/parser.c \
			Criterion/tester/prompt.c

OBJ = ${SRCS:.c=.o}

#OBJ_TESTS = $(addprefix $(OBJS_DIRECTORY),$(OBJ)) $(SRCS_TEST)
#OBJ_TEST= ${SRCS_TEST:.c=.o}


#OBJS = $(addprefix $(OBJS_DIRECTORY), $(filter-out test.o,$(OBJ)))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJ))


OBJS_TEST = $(filter-out $(OBJS_DIRECTORY)main.o,$(OBJS))

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c
	@$(CC) $(CFLAGS) $< -I$(HEADER) -c -o $@

all : $(FILE_LIB) $(NAME)

$(FILE_LIB) : 
ifeq ("$(wildcard $(FILE_LIB))","")
	@make re -C $(PATH_LIB)
endif

$(NAME) : $(OBJS)
	@$(CC) $(CLFAGS) $(OBJS) -lncurses -L$(PATH_LIB) -l$(LIBFT) -o $(NAME)

action : fclean test


test : $(FILE_LIB) $(OBJS)
	@$(CC) $(OBJS_TEST) $(SRCS_TEST) -I$(HEADER) -lcriterion -lncurses -L$(PATH_LIB) -l$(LIBFT) -o $(NAME_TEST)

tester: re
	@sh Criterion/build.sh


# --verbose

clean : 
	@$(RM) $(NAME)
	@$(RM) $(NAME_TEST)

fclean : clean
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_TEST)
#	@make fclean -C libft

clear : 
ifeq ("$(wildcard $(FILE_LIB))","$(FILE_LIB)")
	@make fclean -C $(PATH_LIB)
endif

re : fclean all
