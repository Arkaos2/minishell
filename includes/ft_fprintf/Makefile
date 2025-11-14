# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 16:27:08 by saibelab          #+#    #+#              #
#    Updated: 2025/11/14 16:27:10 by saibelab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_fprintf.a

SRC = ft_fprintf.c \
		ft_fprintf_types.c \
		ft_fprintf_types_utils.c \
		ft_fprintf_utils.c \
		utils.c

INC = ft_fprintf.h

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus
