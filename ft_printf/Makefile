# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 14:38:44 by marco             #+#    #+#              #
#    Updated: 2025/04/23 12:24:30 by marcoga2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#newline with \
# compilation variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
NAME = libftprintf.a

# compulsory files
SRCS = ft_printf.c number_management.c print_type.c endpoint.c
OBJS = $(SRCS:.c=.o)

# rules
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean re fclean

