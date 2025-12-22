# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 18:56:32 by saibelab          #+#    #+#              #
#    Updated: 2025/12/22 19:12:30 by saibelab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -Ilibft/includes -Iincludes
LDFLAGS			= -lreadline

SRCS			= src/main.c \
			src/gc.c \
			src/environement/environement.c \
			src/exec/check_path.c \
			src/exec/fill_env.c \
			src/exec/exec.c \
			src/exec/pipes.c \
			src/exec/free.c \
			src/exec/redirection.c \
			src/exec/here_doc.c \
			src/parse/list.c \
			src/parse/outils.c \
				src/parse/expand_dollars.c \
			src/parse/redirs.c \
			src/parse/quotes.c \
			src/parse/lexing.c \
			src/builtins/builtin_check.c \
			src/builtins/echo.c \
			src/builtins/env.c \
			src/builtins/cd.c \
			src/builtins/pwd.c \
			src/builtins/export.c



OBJS			= $(SRCS:.c=.o)

LIBFT_PATH		= includes/libft
LIBFT			= $(LIBFT_PATH)/libft.a

FT_FPRINTF_PATH	= includes/ft_fprintf
FT_FPRINTF		= $(FT_FPRINTF_PATH)/ft_fprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_FPRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_FPRINTF) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(FT_FPRINTF):
	@$(MAKE) -C $(FT_FPRINTF_PATH)

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(FT_FPRINTF_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C  $(LIBFT_PATH) fclean
	@$(MAKE) -C $(FT_FPRINTF_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus
