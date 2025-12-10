#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_fprintf/ft_fprintf.h"
# include "libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_gcnode
{
	void			*ptr;
	struct s_gcnode	*next;
}					t_gcnode;

typedef struct s_gc
{
	t_gcnode		*head;
}					t_gc;

t_gc				*gc_new(void);
void				gc_destroy(t_gc *gc);
void				*gc_calloc(t_gc *gc, size_t size);
char				*gc_strdup(t_gc *gc, const char *s);
char				*gc_strndup(t_gc *gc, const char *s, int n);
t_gcnode			*new_node(void *ptr);

typedef struct s_envp
{
	char			*key;
	char			*value;
	t_gc			*gc;
	struct s_envp	*next;
}					t_envp;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type type; // R_IN, R_OUT, etc.
	char *file;        // le fichier associé (<, >, >>, <<)
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char **args;     // ["ls", "-l", NULL]
	t_redir *redirs; // liste de redirections
	pid_t			pid;
	t_token			*tok;
	t_gc *gc;           // pour fork
	struct s_cmd *next; // prochaine commande (pipe)
}					t_cmd;

void				free_array(char **av);
void				ultime_lexing(t_token **tok, char *str, t_gc *gc);
void				ultime_filler(t_cmd *cmd);
void				lstadd_backtok(t_token **lst, t_token *new);
void				lstadd_backredir(t_redir **lst, t_redir *new);

char				*key_finder(char *envp);

t_envp				*create_envp(char **envp);
t_envp				*check_node(char *envp);

int					is_whitespace(char *s);
int					readline_check(t_envp *env);

t_cmd				*init_struct(void);

t_token				*lstnew_token(t_gc *gc, char *value, t_token_type type);

t_redir				*lstnew_redir(t_gc *gc, char *value, t_redir_type type);

#endif
