/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:04:31 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/09 18:09:20 by saibelab         ###   ########.fr       */
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

void	run_pipes(t_exec *exec)
{
	int		status;
	t_cmd	*cmd;

	exec->nb_cmd = count_cmds(exec->cmd_list);
	exec->pipes = create_pipes(exec->nb_cmd, exec->gc);
	if (!exec->pipes && exec->nb_cmd > 1)
		cleanup_on_error(exec);
	if (!exec->pipes && exec->nb_cmd > 1)
	{
		perror("pipe");
		return ;
	}
	signal(SIGINT, heredoc_sigint_handler);
	fill_all_heredocs(exec->gc, exec->cmd_list);
	signal(SIGINT, SIG_DFL);
	run_children(exec);
	close_all_pipes(exec->pipes, exec->nb_cmd);
	cmd = exec->cmd_list;
	exec->last_exit = 0;
	while (cmd)
	{
		if (waitpid(cmd->pid, &status, 0) > 0)
			if (WIFEXITED(status))
				exec->last_exit = WEXITSTATUS(status);
		cmd = cmd->next;
	}
	exec->pipes = NULL;
}


