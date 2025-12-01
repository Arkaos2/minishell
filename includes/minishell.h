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

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_cmd
{
	char **args;        // ["ls", "-l", NULL]
	char *infile;       // pour <
	char *outfile;      // pour > ou >>
	int append;         // 0 ou 1 (>>)
	int heredoc;        // 0 ou 1 (<<)
	char *limiter;      // délimiteur du heredoc
	struct s_cmd *next; // prochaine commande (|)
}					t_cmd;

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

void				free_array(char **av);

char				*key_finder(char *envp);

t_envp				*create_envp(char **envp);
t_envp				*check_node(char *envp);

int					is_whitespace(char *s);
int					readline_check(t_envp *env);
int					redir_inxheredoc(t_token **tok, char *str, int *i);

t_cmd				*init_cmd(void);

t_token				*lstnew_token(char *value, t_token_type type);

#endif
