/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:19:46 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/09 17:27:43 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*handle_pipe(t_shell *s, t_cmd *cmd)
{
	cmd->next = init_cmd(s);
	if (!cmd->next)
		return (NULL);
	return (cmd->next);
}

int	redir_outxappend(t_token **tok, char *str, int *i, t_gc *gc)
{
	t_token	*node;

	if (str[*i] != '>')
		return (0);
	if (str[*i + 1] == '>')
	{
		node = lstnew_token(gc, ">>", TOKEN_REDIR_APPEND);
		if (!node)
			return (0);
		lstadd_backtok(tok, node);
		*i += 2;
		return (1);
	}
	node = lstnew_token(gc, ">", TOKEN_REDIR_OUT);
	if (!node)
		return (0);
	lstadd_backtok(tok, node);
	(*i)++;
	return (1);
}

int	redirs_syntax(t_shell *shell)
{
	t_token	*tok;

	if (!shell)
		return (0);
	tok = shell->tok;
	while (tok)
	{
		if (tok->type == TOKEN_PIPE)
		{
			if (!tok->next || tok->next->type == TOKEN_PIPE)
				return (shell->exec->last_exit = 2, ft_fprintf(2,
						"bash: syntax error near unexpected token `|'\n"), 0);
		}
		if (tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_HEREDOC)
		{
			if (!tok->next || tok->next->type != TOKEN_WORD)
				return (shell->exec->last_exit = 2, ft_fprintf(2,
						"bash: syntax error "), ft_fprintf(2,
						"near unexpected token `%s'\n", tok->value), 0);
		}
		tok = tok->next;
	}
	return (1);
}

t_redir	*alloc_redir_with_file(t_token *tok, t_shell *shell)
{
	t_redir	*node;
	char	*res;
	char	*tmp;

	node = gc_calloc(shell->gc, sizeof(t_redir));
	if (!node)
		return (NULL);
	if (tok->next->quote == 2)
	{
		res = gc_strdup(shell->gc_tmp, tok->next->value);
		if (!res)
			return (NULL);
	}
	else
	{
		tmp = expand_dollars(shell, tok->next->value);
		if (!tmp)
			return (NULL);
		res = gc_strdup(shell->gc_tmp, tmp);
		if (!res)
			return (NULL);
	}
	node->file = res;
	node->quoted = (tok->next->quote == 2);
	node->next = NULL;
	return (node);
}

void	set_redir_type(t_redir *node, t_token *tok)
{
	if (tok->type == TOKEN_REDIR_IN)
		node->type = R_IN;
	else if (tok->type == TOKEN_REDIR_OUT)
		node->type = R_OUT;
	else if (tok->type == TOKEN_REDIR_APPEND)
		node->type = R_APPEND;
	else if (tok->type == TOKEN_HEREDOC)
		node->type = R_HEREDOC;
}
