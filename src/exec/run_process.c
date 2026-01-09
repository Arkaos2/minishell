/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:18:46 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/05 20:18:54 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_builtin(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->exec->cmd_list;
	if (shell->exec->nb_cmd == 1
		&& cmd && cmd->args && cmd->args[0]
		&& is_builtin(cmd->args[0])
		&& cmd->redirs == NULL)
	{
		shell->exec->last_exit = handle_builtin(cmd, shell);
		return (1);
	}
	return (0);
}

static int	check_all_redirs(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->exec->cmd_list;
	while (cmd)
	{
		if (!check_redirs(cmd))
		{
			shell->exec->last_exit = 1;
			return (0);
		}
		cmd = cmd->next;
	}
	return (1);
}

static int	init_pipes(t_shell *shell)
{
	shell->exec->pipes = create_pipes(shell->exec->nb_cmd, shell->gc);
	if (!shell->exec->pipes && shell->exec->nb_cmd > 1)
	{
		cleanup_on_error(shell);
		perror("pipe");
		return (0);
	}
	return (1);
}

static void	wait_for_children(t_shell *shell)
{
	int		status;
	int		sig;
	t_cmd	*cmd;

	cmd = shell->exec->cmd_list;
	while (cmd)
	{
		if (waitpid(cmd->pid, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				shell->exec->last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				shell->exec->last_exit = 128 + sig;
			}
		}
		cmd = cmd->next;
	}
}

void	run_pipes(t_shell *shell)
{
	if (!shell || !shell->exec)
		return ;
	shell->exec->nb_cmd = count_cmds(shell->exec->cmd_list);
	if (handle_single_builtin(shell))
		return ;
	if (!check_all_redirs(shell))
		return ;
	if (!init_pipes(shell))
		return ;
	if (fill_all_heredocs(shell) == -1)
	{
		shell->exec->last_exit = 130;
		return ;
	}
	run_children(shell);
	close_all_pipes(shell->exec->pipes, shell->exec->nb_cmd);
	wait_for_children(shell);
	shell->exec->pipes = NULL;
}
