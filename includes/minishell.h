#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "libft/libft.h"
# include "ft_fprintf/ft_fprintf.h"


typedef struct s_gcnode
{
	void			*ptr;
	struct s_gcnode	*next;
}				t_gcnode;

typedef struct s_gc
{
	t_gcnode		*head;
}	t_gc;

typedef struct s_lexer {
	char	*input;
	int		i;
	int		length;
} t_lexer;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

char *key_finder(char *envp);
t_envp *create_envp(char **envp);
t_envp *check_node(char *envp);

int	is_whitespace(char *s);
int	readline_check(t_envp *env);

#endif
