/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:15:48 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/05 20:03:02 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_struct(void)
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

void	run_interactive(t_shell *shell)
{
	char	*line;
	int		ret;

	while (1)
	{
		ret = handle_readline(shell, &line);
		if (ret == 0)
			break ;
		if (ret == -1)
			continue ;
		shell->gc_tmp = gc_new();
		shell->cmd = init_cmd(shell);
		if (!shell->cmd)
			return (free(line), (void)0);
		shell->exec->cmd_list = shell->cmd;
		if (!process_interactive_line(shell, line))
			reset_element(shell);
		if (g_last_signal)
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
