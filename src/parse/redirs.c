/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:23:51 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/08 21:10:00 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_args(t_cmd *cmd, int *i)
{
	char	*res;

	if (!cmd->tok || cmd->tok->type != TOKEN_WORD)
		return (0);
	res = gc_strdup(cmd->gc, cmd->tok->value);
	if (!res)
		return (0);
	cmd->args[(*i)++] = res;
	if (!cmd->args[*i])
		return (0);
	return (1);
}

static t_redir	*pre_fill_redirs(t_cmd *cmd)
{
	t_redir	*node;
	char	*res;

	node = gc_calloc(cmd->gc, sizeof(t_redir));
	if (!node)
		return (NULL);
	res = gc_strdup(cmd->gc, cmd->tok->next->value);
	if (!res)
		return (NULL);
	node->file = res;
	if (!node->file)
		return (NULL);
	if (cmd->tok->type == TOKEN_REDIR_IN)
		node->type = R_IN;
	else if (cmd->tok->type == TOKEN_REDIR_OUT)
		node->type = R_OUT;
	else if (cmd->tok->type == TOKEN_REDIR_APPEND)
		node->type = R_APPEND;
	else if (cmd->tok->type == TOKEN_HEREDOC)
		node->type = R_HEREDOC;
	node->next = NULL;
	return (node);
}

static int	fill_redirs(t_cmd *cmd)
{
	t_redir	*node;

	if (!cmd->tok || !cmd->tok->next || cmd->tok->next->type != TOKEN_WORD)
		return (0);
	if (cmd->tok->type == 2 || cmd->tok->type == 3 || cmd->tok->type == 4
		|| cmd->tok->type == 5)
	{
		node = pre_fill_redirs(cmd);
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

t_cmd	*next_cmd(t_cmd *cmd)
{
	t_cmd	*cur;
	t_cmd	*new;

	if (!cmd->tok || cmd->tok->type != TOKEN_PIPE)
		return (NULL);
	cur = cmd;
	new = init_struct();
	if (!new)
	{
		gc_destroy(cmd->gc);
		free(cmd);
		exit(ENOMEM);
	}
	cur->next = new;
	cur = new;
	return (cur);
}

void	ultime_filler(t_cmd *cmd)
{
	t_token	*tok;
	t_cmd	*cur;
	int		v;

	v = 0;
	cur = cmd;
	tok = cmd->tok;
	while (cur->tok)
	{
		// if (cur->tok->type == TOKEN_PIPE)
		// {
		// 	v = 0;
		// 	next_cmd(cur);
		// 	cur = cur->next;
		// }
		if (fill_redirs(cur))
		{
			if (cur->tok && cur->tok->next)
				cur->tok = cur->tok->next->next;
			else
				cur->tok = NULL;
			continue ;
		}
		if (fill_args(cur, &v))
		{
			cur->tok = cur->tok->next;
			continue ;
		}
		cur->tok = cur->tok->next;
	}
}
