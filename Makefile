# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/13 00:29:26 by pduhard-     #+#   ##    ##    #+#        #
#    Updated: 2019/03/24 09:57:02 by pduhard-    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#__________CONFIG__________#

NAME		=	minishell

CC			=	gcc
FLAGS		=	-g -Wall -Werror -Wextra
LIB_FLAGS	=	-L$(LIB_PATH) $(LIB_FLAG)
INCLUDES	=	includes/minishell.h

SRC_PATH	=	./srcs/
BIN_PATH	=	./bin/
LIB_PATH	=	./libft/

SRC			=	main.c				\
				init_shell.c		\
				prompt.c			\
				utils.c				\
				environ.c			\
				history.c			\
				parse_command.c		\
				parse_cmd_arg.c		\
				autocompletion.c	\
				autocomp_search.c	\
				autocomp_find_bin.c	\
				dir_stack.c			\
				dolar_exp.c			\
				tilde_exp.c			\
				tilde_utils.c		\
				find_bin.c			\
				builtin.c			\
				exec.c				\
				free.c				\
				get_command.c		\
				input_manager.c		\
				input_utils.c		\
				input_exec.c		\
				ft_echo.c			\
				ft_exit.c			\
				ft_cd.c				\
				cd_error.c			\
				ft_env.c			\
				ft_env_utils.c		\
				env_options.c		\
				ft_setenv.c			\
				ft_unsetenv.c		\

BIN			=	$(SRC:.c=.o)

LIB_FLAG			=	-lft
LIB					=	libft.a

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BINS		=	$(addprefix $(BIN_PATH), $(BIN))
LIBS		=	$(addprefix $(LIB_PATH), $(LIB))

.PHONY: all clean fclean re lib

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME)

	@make -C libft

$(NAME): $(LIBS) $(BINS)

	@$(CC) -I $(INCLUDES) $(FLAGS) $(LIB_FLAGS) $^ -o $@
	@echo "\n\n$(B)[EXECUTABLE \"$(NAME)\" READY]\n"

$(LIBS):

	@make -C $(LIB_PATH)

$(BIN_PATH)%.o: $(SRC_PATH)%.c $(INCLUDES)

	@mkdir -p $(BIN_PATH) || true
	@$(CC) $(FLAGS) -I $(INCLUDES) -o $@ -c $< && echo "${G} \c"

clean:

	@make clean -C $(LIB_PATH)
	@echo "${R}[CLEANING $(NAME) BINARIES]"
	@rm -f $(BINS)

fclean: clean

	@echo "\n${R}[REMOVING "libft.a"]"
	@rm -rf $(LIB_PATH)/libft.a
	@echo "\n${R}[REMOVING \"$(NAME)\"]\n"
	@rm -f $(NAME)

re: fclean all
