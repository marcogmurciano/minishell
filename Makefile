# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 11:28:00 by dbarba-v          #+#    #+#              #
#    Updated: 2025/07/15 14:52:16 by dbarba-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

INCLUDES = -I./include -I./libft/include

LIBS = -lreadline -L./libft/lib -lft 
LIBFT = ./libft/lib/libft.a

SRCS = 	src/main.c \
		src/debug.c \
		src/prompt/prompt_input.c \
		src/prompt/prompt_utils.c \
		src/environment/get_environment_array.c \
		src/environment/regenerate_environment.c \
		src/environment/check_environment.c \
		src/signals/sigint_handler.c \
		src/tokenization/add_token.c \
		src/tokenization/create_token.c \
		src/tokenization/handler.c \
		src/tokenization/tokenizer_utils.c \
		src/tokenization/tokenizer.c \
		src/expansion/check_token_list.c \
		src/expansion/expander_utils.c \
		src/expansion/expander.c \
		src/expansion/retrieve_input.c \
		src/freeing_utils/array_i.c \
		src/freeing_utils/environ_list.c \
		src/freeing_utils/minishell.c \
		src/freeing_utils/token_list.c \
		src/freeing_utils/cmds.c \
		src/refine/refine_token_roles.c \
		src/syntax/syntax_analysis.c \
		src/syntax/syntax_analysis_utils.c \
		src/syntax/syntax_check.c \
		src/syntax/syntax_getcmd.c \
		src/initialization/minishell.c \
		src/error/malloc.c \
		src/error/syntax.c \
		src/exits/minishell.c \
		src/execution/execution.c \
		src/execution/mini_pipex/exec_commands.c \
		src/execution/mini_pipex/manage_sons.c \
		src/execution/mini_pipex/pipex_utils.c \
		src/execution/mini_pipex/pipex_utils2.c \
		src/execution/mini_pipex/pipex.c \
		src/builtins/builtin_pwd.c \
		src/builtins/builtin_env.c \
		src/builtins/builtin_export.c \


	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: cleanlibft
	$(RM) $(OBJS)

fclean: clean fcleanlibft
	$(RM) $(NAME)

cleanlibft:
	make -C ./libft/ clean

fcleanlibft: cleanlibft
	make -C ./libft/ fclean

re: fclean all

.PHONY: all clean fclean re libft cleanlibft fcleanlibft
