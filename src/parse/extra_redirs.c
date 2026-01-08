/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:19:46 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/08 16:44:54 by saibelab         ###   ########.fr       */
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
				return (shell->exec->last_exit = 1,
					ft_fprintf(2, "bash: syntax error "
						"near unexpected token `|'\n"), 0);
		}
		if (tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_REDIR_APPEND)
		{
			if (!tok->next || tok->next->type != TOKEN_WORD)
				return (shell->exec->last_exit = 1,
					ft_fprintf(2, "bash: syntax error",
						" near unexpected token `%s'\n", tok->value), 0);
		}
		tok = tok->next;
	}
	return (1);
}
