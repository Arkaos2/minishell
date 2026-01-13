/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:00:00 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/13 15:46:24 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_heredoc_line(t_shell *shell, char *line, int expand)
{
	char	*part;
	char	*tmp;

	if (expand)
	{
		tmp = expand_dollars(shell, line);
		if (!tmp)
			return (NULL);
		part = gc_strdup(shell->gc, tmp);
		if (!part)
			return (NULL);
	}
	else
	{
		part = gc_strdup(shell->gc, line);
		if (!part)
			return (NULL);
	}
	return (part);
}

static char	*read_heredoc(t_shell *shell, char *delimiter, int expand)
{
	char	*line;
	char	*content;
	char	*part;

	content = gc_strdup(shell->gc, "");
	heredoc_signal_distributor();
	if (!content)
		return (signal_distributor(), NULL);
	while (1 && content)
	{
		line = readline("> ");
		if (g_last_signal == SIGINT)
			return (free(line), signal_distributor(), NULL);
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line), signal_distributor(), content);
		part = process_heredoc_line(shell, line, expand);
		if (!part)
			return (signal_distributor(), NULL);
		content = gc_strjoin(shell->gc, content, part);
		content = gc_strjoin(shell->gc, content, "\n");
		free(line);
	}
	return (signal_distributor(), content);
}

static int	fill_cmd_heredocs(t_shell *shell, t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
				r->heredoc_content = read_heredoc(shell, r->file, !r->quoted);
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
	t_redir	*r;
	int		pipefd[2];

	(void)shell;
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
