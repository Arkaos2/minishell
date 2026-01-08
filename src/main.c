/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:15:48 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/06 20:02:15 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_shell	*init_struct(void)
{
	t_shell	*shell;
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
	shell->exec->pipes = NULL;
	shell->exec->nb_cmd = 0;
	shell->exec->last_exit = 0;
	return (shell);
}

t_cmd	*init_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = gc_calloc(shell->gc_tmp, sizeof(t_cmd));
	if (!cmd)
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
			continue;
		}
		shell = init_struct();
		if (!shell)
			return (free(line), (void)0);
		shell->gc_tmp = gc_new();
		shell->env = create_envp(shell->gc, envp);
		upgrade_env(shell);
		shell->cmd = init_cmd(shell);
		shell->exec->cmd_list = shell->cmd;
		shell->tok = NULL;
		if (!ultime_lexing(&shell->tok, line, shell->gc_tmp, shell))
		{
			gc_destroy(shell->gc_tmp);
			free(line);
			continue ;
		}
		if (shell->tok)
		{
			if (!ultime_filler(shell))
			{
				reset_element(shell);
				free(line);
				continue ;
			}
			run_pipes(shell);
		}
		gc_destroy(shell->gc_tmp);
		gc_destroy(shell->gc);
		free(line);
	}
}

static void	run_interactive(t_shell *shell)
{
	char	*line;

	while (1)
	{
		g_last_signal = 0;
		line = readline("minishell: ");
		if (!line)
			break;
		if (g_last_signal == 130)
			shell->exec->last_exit = 130;
		if (*line && !is_whitespace(line))
			add_history(line);
		if(check_syntaxe(line) == 0)
		// add le exit code 2
			continue;
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
		if (!redirs_syntax(shell->tok))
		{
			reset_element(shell);
			free(line);
			continue ;
		}
		if (shell->tok)
		{
			if (!ultime_filler(shell))
			{
				reset_element(shell);
				free(line);
				continue ;
			}
			run_pipes(shell);
		}
		if(g_last_signal)
		{
			shell->exec->last_exit = 128 + g_last_signal;
			g_last_signal = 0;
		}
		reset_element(shell);
		free(line);
		printf("%d ", shell->exec->last_exit);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		status;

	(void)argv;
	if (argc != 1)
	{
		write(STDERR_FILENO, "minishell: too many arguments\n", 30);
		return (1);
	}
	if (!isatty(STDIN_FILENO))
		return (run_non_interactive(envp), 0);
	shell = init_struct();
	if (!shell)
		return (1);
	shell->env = create_envp(shell->gc, envp);
	upgrade_env(shell);
	signal_distributor();
	run_interactive(shell);
	status = shell->exec->last_exit;
	return (gc_destroy(shell->gc), status);
}
