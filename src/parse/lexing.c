/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:45:01 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/13 18:31:20 by saibelab         ###   ########.fr       */
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

static char	*extract_word_content(char *str, int *i, t_shell *s, int *quotes)
{
	char	*word;
	char	*tmp;

	word = gc_strdup(s->gc_tmp, "");
	if (!word)
		return (NULL);
	while (word && str[*i] && !is_separator(str[*i]))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			if (str[*i] == '"')
				tmp = double_quotes(str, i, s->gc_tmp);
			else
			{
				*quotes = 1;
				tmp = single_quote(str, i, s->gc_tmp);
			}
			if (!tmp)
				return (NULL);
			word = gc_strjoin(s->gc_tmp, word, tmp);
		}
		else
			word = append_char(s->gc_tmp, word, str[(*i)++]);
	}
	return (word);
}

int	tokenword(t_token **tok, char *str, int *i, t_shell *s)
{
	char	*final_word;
	t_token	*node;
	int		quotes;

	quotes = 0;
	final_word = extract_word_content(str, i, s, &quotes);
	if (!final_word)
		return (0);
	node = lstnew_token(s->gc_tmp, final_word, TOKEN_WORD);
	if (!node)
		return (0);
	if (quotes)
		node->quote = 1;
	lstadd_backtok(tok, node);
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

int	process_token(t_token **tok, char *str, int *v, t_gc *gc)
{
	if (redir_inxheredoc(tok, str, v, gc))
		return (1);
	if (redir_outxappend(tok, str, v, gc))
		return (1);
	if (tokenpipe(tok, str, v, gc))
		return (1);
	return (0);
}
