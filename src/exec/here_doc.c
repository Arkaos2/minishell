/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:00:00 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/02 17:01:09 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_heredoc_content(t_shell *shell, char *delimiter)
{
	char	*line;
	char	*content;

	heredoc_signal_distributor();
	content = gc_strdup(shell->gc, "");
	while (1)
	{
		line = readline("heredoc> ");
		if (g_last_signal == SIGINT)
		{
			free(line);
			signal_distributor();
			return (NULL);
		}
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		content = gc_strjoin(shell->gc, content, line);
		content = gc_strjoin(shell->gc, content, "\n");
		free(line);
	}
	signal_distributor();
	return (content);
}

static int	fill_cmd_heredocs(t_shell *shell, t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			r->heredoc_content = read_heredoc_content(shell, r->file);
			if (r->heredoc_content == NULL)
				return (-1);
		}
		r = r->next;
	}
	return (0);
}

int	fill_all_heredocs(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->exec->cmd_list;
	while (cmd)
	{
		if (fill_cmd_heredocs(shell, cmd) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}

int	setup_heredoc_input(t_shell *shell, t_cmd *cmd)
{
	(void)shell;
	t_redir	*r;
	int		pipefd[2];

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				return (-1);
			}
			write(pipefd[1], r->heredoc_content, ft_strlen(r->heredoc_content));
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			break ;
		}
		r = r->next;
	}
	return (0);
}
