/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:49:43 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/01 18:32:43 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_outxappend(t_token **tok, char *str)
{
	t_token	*node;

	if (!str)
		return (0);
	if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			node = lstnew_token(ft_strdup(">>"), TOKEN_HEREDOC);
			if (!node)
				return (0);
			ft_lstadd_back(tok, node);
			*i += 2;
		}
		else
		{
			node = lstnew_token(ft_strdup(">"), TOKEN_REDIR_IN);
			if (!node)
				return (0);
			ft_lstadd_back(tok, node);
			*i++;
		}
		return (1);
	}
	return (0);
}

int	redir_inxheredoc(t_token **tok, char *str, int *i)
{
	t_token	*node;

	if (!str)
		return (0);
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			node = lstnew_token(ft_strdup("<<"), TOKEN_HEREDOC);
			if (!node)
				return (0);
			ft_lstadd_back(tok, node);
			*i += 2;
		}
		else
		{
			node = lstnew_token(ft_strdup("<"), TOKEN_REDIR_IN);
			if (!node)
				return (0);
			ft_lstadd_back(tok, node);
			*i++;
		}
		return (1);
	}
	return (0);
}

void	ultime_lexing(t_token **tok, char *str)
{
	int	v;

	v = 0;
	while (str[v])
	{
		if (redir_inxheredoc(tok, str, &v))
			continue ;
		if (redir_outxappend(tok, str, &v))
			continue ;
	}
}
