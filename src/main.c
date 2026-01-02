/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:15:48 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/31 18:58:17 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_shell	*init_struct(void)
{
	t_shell	*shell;
	// size_t	v;
	t_gc	*gc;

	gc = gc_new();
	if (!gc)
		return (NULL);
	shell = gc_calloc(gc, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->gc = gc;
	shell->exec = gc_calloc(gc, sizeof(t_exec));
	if (!shell->exec)
		return (NULL);
	return (shell);
}

static t_cmd	*init_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	size_t	v;

	cmd = gc_calloc(shell->gc_tmp, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	v = sizeof_arg(shell);
	if (v == 0)
		v = 1;
	cmd->args = gc_calloc(shell->gc_tmp, sizeof(char *) * (v + 2));
	if (!cmd->args)
		return (NULL);
	return (cmd);
}

static void	run_non_interactive(char **envp)
{
	t_shell	*shell;
	char	*line;
	size_t	len;

	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		len = ft_strlen(line);
		if (len && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		shell = init_struct();
		if (!shell)
			return (free(line), (void)0);
		shell->gc_tmp = gc_new();
		shell->env = create_envp(shell->gc, envp);
		shell->cmd = init_cmd(shell);
		shell->exec->cmd_list = shell->cmd;
		shell->tok = NULL;
		if (!ultime_lexing(&shell->tok, line, shell->gc_tmp, shell))
		{
			gc_destroy(shell->gc_tmp);
			gc_destroy(shell->gc);
			free(line);
			continue ;
		}
		if (shell->tok)
		{
			ultime_filler(shell);
			run_pipes(shell);
		}
		gc_destroy(shell->gc_tmp);
		shell->tok = NULL;
		free(line);
	}
}

static void	run_interactive(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break ;
		if (!*line || is_whitespace(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (check_syntaxe(line) == 0)
			continue ;
		shell->gc_tmp = gc_new();
		shell->cmd = init_cmd(shell);
		if (!shell->cmd)
			return (free(line), (void)0);
		shell->exec->cmd_list = shell->cmd;
		if (!ultime_lexing(&shell->tok, line, shell->gc_tmp, shell))
		{
			reset_element(shell);
			free(line);
			continue ;
		}
		if (shell->tok)
		{
			ultime_filler(shell);
			run_pipes(shell);
		}
		reset_element(shell);
		free(line);
	}
}

// static void	run_interactive(t_shell *shell)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("minishell: ");
// 		if (!line)
// 			break ;
// 		if (*line && !is_whitespace(line))
// 			add_history(line);
// 		if (check_syntaxe(line) == 0)
// 			continue ;
// 		shell->cmd = init_cmd(shell);
// 		if (!shell->cmd)
// 			return (free(line), (void)0);
// 		shell->exec->cmd_list = shell->cmd;
// 		if (!ultime_lexing(&shell->tok, line, shell->gc, shell))
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		if (shell->tok)
// 		{
// 			ultime_filler(shell);
// 			run_pipes(shell);
// 		}
// 		free(line);
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	if (!isatty(STDIN_FILENO))
		return (run_non_interactive(envp), 0);
	shell = init_struct();
	if (!shell)
		return (1);
	shell->env = create_envp(shell->gc, envp);
	run_interactive(shell);
	gc_destroy(shell->gc);
	return (0);
}
