/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:23:51 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/31 19:21:36 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_args(t_token *tok, t_shell *shell, t_cmd *cmd, int *i)
{
	char	*res;

	if (!tok || tok->type != TOKEN_WORD)
		return (0);
	if (shell->tok->quote == 1)
	{
		res = gc_strdup(shell->gc_tmp, tok->value);
		if (!res)
			return (0);
	}
	else
	{
		res = expand_dollars(shell, tok->value);
		if (!res)
			return (0);
	}
	cmd->args[(*i)] = res;
	if (!cmd->args[*i])
		return (0);
	(*i)++;
	// printf("DEBUG: writing at index %d\n", *i);
	return (1);
}

static t_redir	*pre_fill_redirs(t_token *tok, t_shell *shell)
{
	t_redir	*node;
	char	*res;

	node = gc_calloc(shell->gc_tmp, sizeof(t_redir));
	if (!node)
		return (NULL);
	res = gc_strdup(shell->gc_tmp, tok->next->value);
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

static int	fill_redirs(t_token *tok, t_shell *s, t_cmd *cmd)
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

t_cmd	*next_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	size_t	v;

	cmd = gc_calloc(shell->gc_tmp, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	v = sizeof_arg(shell);
	if (v == 0)
		v = 1;
	cmd->args = gc_calloc(shell->gc_tmp, sizeof(char *) * (v + 2));
	if (!cmd->args)
		return (NULL);
	printf("DEBUG: malloc args size = %zu\n", v + 1);
	return (cmd);
}

void	ultime_filler(t_shell *s)
{
	t_cmd	*cmd;
	int		v;
	t_token	*tok;

	v = 0;
	cmd = s->cmd;
	tok = s->tok;
	while (tok)
	{
		if (tok->type == TOKEN_PIPE)
		{
			cmd->args[v] = NULL;
			cmd->next = next_cmd(s);
			if (!cmd->next)
			{
				gc_destroy(s->gc);
				perror("minishell:");
				exit(1);
			}
			cmd = cmd->next;
			v = 0;
			tok = tok->next;
			continue ;
		}
		if (fill_redirs(tok, s, cmd))
		{
			if (tok && tok->next)
				tok = tok->next->next;
			else
				tok = NULL;
			continue ;
		}
		if (fill_args(tok, s, cmd, &v))
		{
			tok = tok->next;
			continue ;
		}
		tok = tok->next;
	}
	if (cmd)
        cmd->args[v] = NULL;
}
