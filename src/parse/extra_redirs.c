/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:19:46 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/02 20:35:55 by pmalumba         ###   ########.fr       */
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
