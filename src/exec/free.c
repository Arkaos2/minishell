/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:54:33 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/02 19:32:45 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_on_error(t_exec *exec)
{
	safe_exit(exec, 1);
}

void	safe_exit(t_exec *exec, int code)
{
	if (exec && exec->gc)
		gc_destroy(exec->gc);
	exit(code);
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
