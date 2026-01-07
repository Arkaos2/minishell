/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:08:15 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/05 19:10:20 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_input_redirections(t_redir *redir, t_shell *s)
{
	int	fd;

	while (redir)
	{
		if (redir->type == R_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->file);
				safe_exit(s, 127);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}

static void	open_output_redirections(t_redir *redir, t_shell *s)
{
	int	fd;

	while (redir)
	{
		if (redir->type == R_OUT)
			fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == R_APPEND)
			fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
		{
			redir = redir->next;
			continue;
		}
		if (fd < 0)
		{
			perror(redir->file);
			safe_exit(s, 1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}

static void	open_redirections(t_cmd *cmd, t_shell *s)
{
	open_input_redirections(cmd->redirs, s);
	open_output_redirections(cmd->redirs, s);
}

void	setup_child_fds(t_cmd *cmd, t_shell *shell, int i)
{
	if (i > 0)
		dup2(shell->exec->pipes[(i - 1) % 2][0], STDIN_FILENO);
	if (i < shell->exec->nb_cmd - 1)
		dup2(shell->exec->pipes[i % 2][1], STDOUT_FILENO);
	open_redirections(cmd, shell);
	close_all_pipes(shell->exec->pipes, shell->exec->nb_cmd);
}

int	check_redirs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == R_IN)
		{
			if (access(redir->file, F_OK) != 0)
			{
				perror(redir->file);
				return (0);
			}
		}
		redir = redir->next;
	}
	return (1);
}
