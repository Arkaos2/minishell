/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:04:31 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/01 17:19:32 by saibelab         ###   ########.fr       */
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

void	close_all_pipes(int **pipes, int nb_cmd)
{
	int i;

	if (!pipes)
		return ;
	i = 0;
	while (i < nb_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	cleanup_allocated_pipes(int **pipes, int count)
{
	int j;

	j = 0;
	while (j < count)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		free(pipes[j]);
		j++;
	}
	free(pipes);
}

int **create_pipes(int nb_cmd, t_gc *gc)
{
	int **pipes;
	int i;

	if (nb_cmd <= 1)
		return (NULL);
	pipes = gc_calloc(gc, sizeof(int *) * (nb_cmd - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_cmd - 1)
	{
		pipes[i] = gc_calloc(gc, sizeof(int) * 2);
		if (!pipes[i])
		{
			cleanup_allocated_pipes(pipes, i);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			/* close fds for previously created pipes and current */
			cleanup_allocated_pipes(pipes, i + 1);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	free_pipes(int **pipes, int nb_cmd)
{
	int i;

	if (!pipes)
		return ;
	i = 0;
	while (i < nb_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

