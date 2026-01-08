/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:54:33 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/08 16:34:27 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_on_error(t_shell *shell)
{
	safe_exit(shell, 1);
}

void	safe_exit(t_shell *s, int code)
{
	if (s->gc && s)
	{
		gc_destroy(s->gc_tmp);
		gc_destroy(s->gc);
	}
	exit(code);
}

void	close_all_pipes(int **pipes, int nb_cmd)
{
	int	i;

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
