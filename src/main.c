/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:15:48 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/01 18:15:45 by saibelab         ###   ########.fr       */
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

static t_cmd	*init_cmd(t_gc *gc)
{
	t_cmd	*cmd;

	cmd = gc_calloc(gc, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = gc_calloc(gc, sizeof(char *) * 100);
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
			continue;
		}
		shell = init_struct();
		if (!shell)
			return (free(line), (void)0);
		shell->env = create_envp(shell->gc, envp);
		upgrade_env(shell);
		shell->cmd = init_cmd(shell->gc);
		shell->exec->cmd_list = shell->cmd;
		shell->tok = NULL;
		ultime_lexing(&shell->tok, line, shell->gc, shell);
		if (shell->tok)
		{
			ultime_filler(shell);
			run_pipes(shell);
		}
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
			continue;
		shell->cmd = init_cmd(shell->gc);
		if (!shell->cmd)
			return (free(line), (void)0);
		shell->exec->cmd_list = shell->cmd;
		shell->tok = NULL;
		ultime_lexing(&shell->tok, line, shell->gc, shell);
		if (shell->tok)
		{
			ultime_filler(shell);
			run_pipes(shell);
		}
		if(g_last_signal)
		{
			shell->exec->last_exit = 128 + g_last_signal;
			g_last_signal = 0;
		}
		free(line);
		printf("%d", shell->exec->last_exit);
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
