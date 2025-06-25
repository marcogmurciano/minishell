# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 11:28:00 by dbarba-v          #+#    #+#              #
#    Updated: 2025/06/25 18:33:07 by dbarba-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

INCLUDES = -I./include -I./libft/include

LIBS = -lreadline -L./libft/lib -lft 
LIBFT = ./libft/lib/libft.a

SRCS = 
	
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
