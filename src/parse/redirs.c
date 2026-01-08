/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:23:51 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/05 18:41:10 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_args(t_token *tok, t_shell *shell, t_cmd *cmd)
{
	char	*res;

	if (!tok || tok->type != TOKEN_WORD)
		return (0);
	if (tok->quote == 1)
	{
		res = gc_strdup(shell->gc, tok->value);
		if (!res)
			return (0);
	}
	else
	{
		res = expand_dollars(shell, tok->value);
		if (!res)
			return (0);
	}
	cmd->args = fill_array(shell, cmd->args, res);
	if (!cmd->args)
		return (0);
	return (1);
}

t_redir	*pre_fill_redirs(t_token *tok, t_shell *shell)
{
	t_redir	*node;
	char	*res;

	node = gc_calloc(shell->gc, sizeof(t_redir));
	if (!node)
		return (NULL);
	res = gc_strdup(shell->gc, tok->next->value);
	if (!res)
		return (NULL);
	node->file = res;
	if (!node->file)
		return (NULL);
	if (tok->type == TOKEN_REDIR_IN)
		node->type = R_IN;
	else if (tok->type == TOKEN_REDIR_OUT)
		node->type = R_OUT;
	else if (tok->type == TOKEN_REDIR_APPEND)
		node->type = R_APPEND;
	else if (tok->type == TOKEN_HEREDOC)
		node->type = R_HEREDOC;
	node->next = NULL;
	return (node);
}

int	fill_redirs(t_token *tok, t_shell *s, t_cmd *cmd)
{
	t_redir	*node;

	if (!tok || !tok->next || tok->next->type != TOKEN_WORD)
		return (0);
	if (tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_HEREDOC)
	{
		node = pre_fill_redirs(tok, s);
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

static void next_fill_redirs(t_token **tok)
{
	if ((*tok)->next)
		*tok = (*tok)->next->next;
	else
		*tok = NULL;
}

int	ultime_filler(t_shell *s)
{
	t_cmd	*cmd;
	t_token	*tok;

	cmd = s->cmd;
	tok = s->tok;
	while (tok)
	{
		if (tok->type == TOKEN_PIPE)
		{
			cmd = handle_pipe(s, cmd);
			if (!cmd)
				return (0);
			tok = tok->next;
		}
		else if (fill_redirs(tok, s, cmd))
		{
			next_fill_redirs(&tok);
		}
		else if (fill_args(tok, s, cmd))
			tok = tok->next;
		else
			tok = tok->next;
	}
	return (1);
}
