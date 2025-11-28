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

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

t_gc		*gc_new(void);
void		*gc_calloc(t_gc *gc, size_t size);
void		gc_destroy(t_gc *gc);
char		*gc_strdup(t_gc *gc, const char *s);
t_gcnode	*new_node(void *ptr);
char		*gc_strndup(t_gc *gc, const char *s, int n);

char		*key_finder(t_gc *gc, char *envp);
t_envp		*create_envp(t_gc *gc, char **envp);
t_envp		*check_node(t_gc *gc, char *envp);

int			is_whitespace(char *s);
int			readline_check(t_envp *env);

#endif
