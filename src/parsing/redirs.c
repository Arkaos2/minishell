/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:23:51 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/11 18:54:12 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_args(t_shell *shell, t_cmd *cmd, int *i)
{
	char	*res;

	if (!shell->tok || shell->tok->type != TOKEN_WORD)
		return (0);
	res = gc_strdup(shell->gc, shell->tok->value);
	if (!res)
		return (0);
	cmd->args[(*i)] = res;
	if (!cmd->args[*i])
		return (0);
	(*i)++;
	return (1);
}

static t_redir	*pre_fill_redirs(t_shell *shell)
{
	t_redir	*node;
	char	*res;

	node = gc_calloc(shell->gc, sizeof(t_redir));
	if (!node)
		return (NULL);
	res = gc_strdup(shell->gc, shell->tok->next->value);
	if (!res)
		return (NULL);
	node->file = res;
	if (!node->file)
		return (NULL);
	if (shell->tok->type == TOKEN_REDIR_IN)
		node->type = R_IN;
	else if (shell->tok->type == TOKEN_REDIR_OUT)
		node->type = R_OUT;
	else if (shell->tok->type == TOKEN_REDIR_APPEND)
		node->type = R_APPEND;
	else if (shell->tok->type == TOKEN_HEREDOC)
		node->type = R_HEREDOC;
	node->next = NULL;
	return (node);
}

static int	fill_redirs(t_shell *s, t_cmd *cmd)
{
	t_redir	*node;

	if (!s->tok || !s->tok->next || s->tok->next->type != TOKEN_WORD)
		return (0);
	if (s->tok->type == 2 || s->tok->type == 3 || s->tok->type == 4
		|| s->tok->type == 5)
	{
		node = pre_fill_redirs(s);
		if (!node)
			return (0);
		if (!cmd->redirs)
			cmd->redirs = node;
		else
			lstadd_backredir(&cmd->redirs, node);
		return (1);
	}
	return (0);
}

t_cmd	*next_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = gc_calloc(shell->gc, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = gc_calloc(shell->gc, sizeof(char *) * 100);
	if (!cmd->args)
		return (NULL);
	return (cmd);
}

void	ultime_filler(t_shell *s)
{
	t_cmd	*cmd;
	int		v;

	v = 0;
	cmd = s->cmd;
	while (s->tok)
	{
		if (s->tok->type == TOKEN_PIPE)
		{
			cmd->next = next_cmd(s);
			if (!cmd->next)
			{
				gc_destroy(s->gc);
				perror("minishell:");
				exit (1);
			}
			cmd = cmd->next;
			v = 0;
			s->tok = s->tok->next;
			continue ;
		}
		if (fill_redirs(s, cmd))
		{
			if (s->tok && s->tok->next)
				s->tok = s->tok->next->next;
			else
				s->tok = NULL;
			continue ;
		}
		if (fill_args(s, cmd, &v))
		{
			s->tok = s->tok->next;
			continue ;
		}
		s->tok = s->tok->next;
	}
}
