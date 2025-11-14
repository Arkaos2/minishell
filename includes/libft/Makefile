# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 15:01:45 by saibelab          #+#    #+#              #
#    Updated: 2025/07/02 14:42:10 by saibelab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c \
ft_atol.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_strchr.c \
ft_strdup.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_tolower.c \
ft_toupper.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
get_next_line_bonus.c \
get_next_line_utils_bonus.c \
ft_printf_utils.c \
ft_printf_str.c \
ft_printf_num.c \
ft_printf.c

SRCS_B = ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstsize_bonus.c \
ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c \
ft_lstclear_bonus.c \
ft_lstiter_bonus.c \
ft_lstmap_bonus.c \



INC = libft.h

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -I. -g
AR = ar rcs
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJS)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c libft.h
		@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(OBJS) $(OBJS_B)
	@$(AR) $(NAME) $(OBJS_B)

clean :
	@$(RM) $(OBJS) $(OBJS_B)

fclean :
	@$(RM) $(NAME) $(OBJS) $(OBJS_B)

re : fclean all

.PHONY : all clean fclean re bonus

