/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:04:31 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/31 17:55:16 by pmalumba         ###   ########.fr       */
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
	t_cmd	*cmd;

	if (!shell || !shell->exec)
		return ;
	shell->exec->nb_cmd = count_cmds(shell->exec->cmd_list);
	if (shell->exec->nb_cmd == 1 && shell->exec->cmd_list
		&& shell->exec->cmd_list->args
		&& shell->exec->cmd_list->args[0]
		&& is_builtin(shell->exec->cmd_list->args[0]))
	{
		shell->exec->last_exit = handle_builtin(shell->exec->cmd_list, shell->env, shell->gc_tmp);
		return ;
	}
	shell->exec->pipes = create_pipes(shell->exec->nb_cmd, shell->gc_tmp);
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
	shell->exec->last_exit = 0;
	while (cmd)
	{
		if (waitpid(cmd->pid, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				shell->exec->last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exec->last_exit = 128 + WTERMSIG(status);
		}
		cmd = cmd->next;
	}
	shell->exec->pipes = NULL;
}


