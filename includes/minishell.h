/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:14:59 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/23 17:12:45 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "ft_fprintf/ft_fprintf.h"
# include "sys/wait.h"

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
	int				quote;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	char 				*heredoc_content;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

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

typedef struct s_shell
{
	t_exec	*exec;
	t_token	*tok;
	t_envp	*env;
	t_cmd	*cmd;
	t_gc	*gc;
	int		status;
}			t_shell;


void		fill_all_heredocs(t_shell *shell);
int			setup_heredoc_input(t_shell *shell, t_cmd *cmd);
void		heredoc_sigint_handler(int sig);

void		free_cmds(t_cmd *cmd);
void		free_envp(t_envp *env);
void		free_exec(t_shell *shell);

t_gc		*gc_new(void);
void		*gc_calloc(t_gc *gc, size_t size);
void		gc_destroy(t_gc *gc);
char		*gc_strdup(t_gc *gc, const char *s);
t_gcnode	*new_node(void *ptr);
char		*gc_strndup(t_gc *gc, const char *s, int n);
char		*gc_strjoin(t_gc *gc, const char *s1, const char *s2);

char		*key_finder(t_gc *gc, char *envp);
t_envp		*create_envp(t_gc *gc, char **envp);
t_envp		*check_node(t_gc *gc, char *envp);

int			is_whitespace(char *s);
int			readline_check(t_envp *env);

char		*get_cmd_path(char *cmd, t_envp *env, t_gc *gc);
int			is_absolute_path(char *cmd);

void		run_children(t_shell *shell);
void		run_pipes(t_shell *shell);
void		exec_child(t_cmd *cmd, t_shell *shell);
void		setup_child_fds(t_cmd *cmd, t_shell *shell, int i);
int			check_redirs(t_cmd *cmd);
void		cleanup_on_error(t_shell *shell);
void		safe_exit(t_shell *shell, int code);

int		is_builtin(char *cmd);
int		handle_builtin(t_cmd *cmd, t_envp *env, t_gc *gc);
int		handle_echo(t_cmd *cmd);
int		handle_env(t_envp *env, int flag);
void		update_env(t_envp *env, char *key, char *value, t_gc *gc);
char		*get_env_value(t_envp *env, char *key);
int		handle_cd(t_cmd *cmd, t_envp *envp, t_gc *gc);
int		handle_pwd(t_envp *env);
int		handle_export(t_cmd *cmd, t_envp *env, t_gc *gc);
int		handle_unset(t_cmd *cmd, t_envp *env, t_gc *gc);

void		print_redirs(t_redir *r);

char		**env_to_char(t_shell *shell);

int		**create_pipes(int n, t_gc *gc);
int		count_cmds(t_cmd *cmd);
void		close_all_pipes(int **pipes, int n);
void		free_pipes(int **pipes, int n);

int		ultime_lexing(t_token **tok, char *str, t_gc *gc, t_shell *s);
t_cmd		*next_cmd(t_shell *shell);
void		free_array(char **av);
void		ultime_filler(t_shell *s);


t_token		*lstnew_token(t_gc *gc, char *value, t_token_type type);
t_redir		*lstnew_redir(t_gc *gc, char *value, t_redir_type type);
void		lstadd_backredir(t_redir **lst, t_redir *new);
void		lstadd_backtok(t_token **lst, t_token *new);

char		*dollars_conv(t_shell *s, char *name);
int			get_var_len(char *s);
char		*expand_dollars(t_shell *s, char *str);
int			check_syntaxe(char *str);

int			readline_check(t_envp *env);
int			double_quotes(t_token **tok, char *str, int *i, t_gc *gc);
int			single_quote(t_token **tok, char *str, int *i, t_gc *gc);
int			handle_quotes(t_token **tok, char *str, int *i, t_shell *s);

#endif
