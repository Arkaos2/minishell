/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:54:33 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/17 15:59:11 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_on_error(t_shell *shell)
{
	safe_exit(shell->gc, 1);
}

void	safe_exit(t_gc *gc, int code)
{
	if (gc)
		gc_destroy(gc);
	exit(code);
}

void	close_all_pipes(int **pipes, int nb_cmd)
{
	int i;

	if (!pipes)
		return ;
	i = 0;
	while (i < nb_cmd - 1 && i < 2)
	{
		if (pipes[i][0] >= 0)
			close(pipes[i][0]);
		if (pipes[i][1] >= 0)
			close(pipes[i][1]);
		i++;
	}
}

