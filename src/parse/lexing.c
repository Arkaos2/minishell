/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:49:43 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/12 16:36:41 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_outxappend(t_token **tok, char *str, int *i, t_gc *gc)
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

static int	redir_inxheredoc(t_token **tok, char *str, int *i, t_gc *gc)
{
	t_token	*node;

	if (str[*i] != '<')
		return (0);
	if (str[*i + 1] == '<')
	{
		node = lstnew_token(gc, "<<", TOKEN_HEREDOC);
		if (!node)
			return (0);
		lstadd_backtok(tok, node);
		*i += 2;
		return (1);
	}
	node = lstnew_token(gc, "<", TOKEN_REDIR_IN);
	if (!node)
		return (0);
	lstadd_backtok(tok, node);
	(*i)++;
	return (1);
}

static int	tokenword(t_token **tok, char *str, int *i, t_gc *gc)
{
	int		start;
	t_token	*node;
	char	*word;

	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|' || str[*i] == ' '
		|| str[*i] == '\t')
		return (0);
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<'
		&& str[*i] != '>' && str[*i] != '|')
	{
		(*i)++;
	}
	word = ft_substr(str, start, *i - start);
	if (!word)
		return (0);
	node = lstnew_token(gc, word, TOKEN_WORD);
	if (!node)
		return (free(word), 0);
	lstadd_backtok(tok, node);
	free(word);
	return (1);
}

static int	tokenpipe(t_token **tok, char *str, int *i, t_gc *gc)
{
	t_token	*node;

	if (str[*i] == '|')
	{
		node = lstnew_token(gc, "|", TOKEN_PIPE);
		if (!node)
			return (0);
		lstadd_backtok(tok, node);
		(*i)++;
		return (1);
	}
	return (0);
}

void	ultime_lexing(t_token **tok, char *str, t_gc *gc)
{
	int	v;

	v = 0;
	while (str[v])
	{
		if (redir_inxheredoc(tok, str, &v, gc))
			continue ;
		if (redir_outxappend(tok, str, &v, gc))
			continue ;
		if (tokenword(tok, str, &v, gc))
			continue ;
		if (tokenpipe(tok, str, &v, gc))
			continue ;
		v++;
	}
}


