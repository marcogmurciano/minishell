# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 11:28:00 by dbarba-v          #+#    #+#              #
#    Updated: 2025/07/17 20:40:58 by dbarba-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

INCLUDES = -I./include -I./libft/include -I./ft_printf

LIBS = -lreadline -L./libft/lib -lft -L./ft_printf -lftprintf
LIBFT = ./libft/lib/libft.a
FT_PRINTF = ./ft_printf/libftprintf.a

SRCS = 	src/main.c \
		src/debug.c \
		src/prompt/prompt_input.c \
		src/prompt/prompt_utils.c \
		src/environment/get_environment_array.c \
		src/environment/regenerate_environment.c \
		src/environment/check_environment.c \
		src/signals/signals.c \
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
		src/syntax/syntax_analysis_utils2.c \
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
		src/execution/mini_pipex/is_cmd_valid.c \
		src/execution/mini_pipex/pipex.c \
		src/execution/mini_pipex/manage_heredoc.c \
		src/execution/mini_pipex/manage_sons_utils.c \
		src/execution/mini_pipex/norminette_is_extremely_fucked_up.c \
		src/builtins/builtin_pwd.c \
		src/builtins/builtin_env.c \
		src/builtins/builtin_export.c \
		src/builtins/builtin_echo.c \
		src/builtins/builtin_unset.c \
		src/builtins/builtin_cd.c \
		src/builtins/builtin_exit.c \
		src/tokenization/join_tokens.c
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C ./libft

$(FT_PRINTF):
	make -C ./ft_printf

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: cleanlibft cleanftprintf
	$(RM) $(OBJS)

fclean: clean fcleanlibft fcleanftprintf
	$(RM) $(NAME)

cleanlibft:
	make -C ./libft/ clean

fcleanlibft: cleanlibft
	make -C ./libft/ fclean

cleanftprintf:
	make -C ./ft_printf/ clean

fcleanftprintf: cleanftprintf
	make -C ./ft_printf/ fclean

re: fclean all

.PHONY: all clean fclean re libft cleanlibft fcleanlibft ft_printf cleanftprintf fcleanftprintf
