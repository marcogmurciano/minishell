# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 11:28:00 by dbarba-v          #+#    #+#              #
#    Updated: 2025/06/30 21:34:34 by dbarba-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = #-Wall -Werror -Wextra
RM = rm -f

INCLUDES = -I./include -I./libft/include

LIBS = -lreadline -L./libft/lib -lft 
LIBFT = ./libft/lib/libft.a

SRCS = 	src/main.c \
		src/prompt/prompt_input.c \
		src/environment/get_environment_array.c \
		src/environment/regenerate_environment.c \
		src/signals/sigint_handler.c \
		src/tokenization/add_token.c \
		src/tokenization/create_token.c \
		src/tokenization/handler.c \
		src/tokenization/tokenizer_utils.c \
		src/tokenization/tokenizer.c \
		src/expansion/check_token_list.c \
		src/expansion/expander_utils.c \
		src/expansion/expander.c \
		src/freeing_utils/environ_list.c \
		src/freeing_utils/minishell.c \
		src/freeing_utils/token_list.c \
		src/exits/minishell.c \
	
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
