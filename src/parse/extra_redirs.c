/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:19:46 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/06 20:06:21 by pmalumba         ###   ########.fr       */
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

int	redirs_syntax(t_token *tok)
{
	while (tok)
	{
		if (tok->type == TOKEN_PIPE)
		{
			if (!tok->next || tok->next->type == TOKEN_PIPE)
				return (ft_fprintf(2, "bash: syntax error near unexpected token `|'\n"), 0);
		}
		if (tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_REDIR_APPEND)
		{
			if (!tok->next || tok->next->type != TOKEN_WORD)
				return (ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n", tok->value),
					0);
		}
		tok = tok->next;
	}
	return (1);
}