/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:04:31 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/01 18:05:02 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static void	cleanup_allocated_pipes(int **pipes, int count)
{
	int j;

	j = 0;
	while (j < count)
	{
		if (pipes[j][0] >= 0)
			close(pipes[j][0]);
		if (pipes[j][1] >= 0)
			close(pipes[j][1]);
		j++;
	}
}

int **create_pipes(int nb_cmd, t_gc *gc)
{
	int **pipes;
	int i;

	if (nb_cmd <= 1)
		return (NULL);
	pipes = gc_calloc(gc, sizeof(int *) * 2);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < 2)
	{
		pipes[i] = gc_calloc(gc, sizeof(int) * 2);
		if (!pipes[i])
		{
			cleanup_allocated_pipes(pipes, i);
			return (NULL);
		}
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
	return (pipes);
}

void run_pipes(t_shell *shell)
{
	int		status;
	int		sig;
	t_cmd	*cmd;

	if (!shell || !shell->exec)
		return ;
	shell->exec->nb_cmd = count_cmds(shell->exec->cmd_list);
	if (shell->exec->nb_cmd == 1 && shell->exec->cmd_list
		&& shell->exec->cmd_list->args
		&& shell->exec->cmd_list->args[0]
		&& is_builtin(shell->exec->cmd_list->args[0]))
	{
		shell->exec->last_exit = handle_builtin(shell->exec->cmd_list, shell);
		return ;
	}
	shell->exec->pipes = create_pipes(shell->exec->nb_cmd, shell->gc);
	if (!shell->exec->pipes && shell->exec->nb_cmd > 1)
		cleanup_on_error(shell);
	if (!shell->exec->pipes && shell->exec->nb_cmd > 1)
	{
		perror("pipe");
		return ;
	}
	fill_all_heredocs(shell);
	run_children(shell);
	close_all_pipes(shell->exec->pipes, shell->exec->nb_cmd);
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
				shell->exec->last_exit = 128 + WTERMSIG(status);
			}
		}
		cmd = cmd->next;
	}
	shell->exec->pipes = NULL;
}


