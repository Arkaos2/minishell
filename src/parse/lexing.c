/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:45:01 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/08 16:45:03 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	process_token(t_token **tok, char *str, int *v, t_gc *gc)
{
	if (redir_inxheredoc(tok, str, v, gc))
		return (1);
	if (redir_outxappend(tok, str, v, gc))
		return (1);
	if (tokenword(tok, str, v, gc))
		return (1);
	if (tokenpipe(tok, str, v, gc))
		return (1);
	return (0);
}

int	ultime_lexing(t_token **tok, char *str, t_gc *gc, t_shell *s)
{
	int	v;
	int	ref;

	v = 0;
	if (!str)
		return (0);
	while (str[v])
	{
		ref = handle_quotes(tok, str, &v, s);
		if (ref == -1)
		{
			ft_fprintf(2,
				"bash: syntax error near unexpected token `newline'\n");
			if (s && s->exec)
				s->exec->last_exit = 2;
			return (0);
		}
		if (ref == 1)
			continue ;
		if (process_token(tok, str, &v, gc))
			continue ;
		v++;
	}
	return (1);
}
