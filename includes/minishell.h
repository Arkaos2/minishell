/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:11:46 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/01 18:40:07 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "ft_fprintf/ft_fprintf.h"
# include "sys/wait.h"

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

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_exec
{
	t_cmd	*cmd_list;
	t_envp	*env;
	int		**pipes;
	int		nb_cmd;
	int		last_exit;
	t_gc	*gc;
}	t_exec;


typedef struct s_gcnode
{
	void			*ptr;
	struct s_gcnode	*next;
}				t_gcnode;

typedef struct s_gc
{
	t_gcnode		*head;
}	t_gc;


void	free_cmds(t_cmd *cmd);
void	free_envp(t_envp *env);
void	free_exec(t_exec *exec);

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

char		*get_cmd_path(char *cmd, t_envp *env);
int			is_absolute_path(char *cmd);

void		run_pipes(t_exec *exec);
void		exec_child(t_cmd *cmd, t_exec *exec);
void		setup_child_fds(t_cmd *cmd, t_exec *exec, int i);
char		**env_to_char(t_envp *env);

int			**create_pipes(int n, t_gc *gc);
int			count_cmds(t_cmd *cmd);
void		close_all_pipes(int **pipes, int n);
void		free_pipes(int **pipes, int n);


#endif
