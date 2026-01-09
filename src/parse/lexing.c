/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:45:01 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/09 17:40:22 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_inxheredoc(t_token **tok, char *str, int *i, t_gc *gc)
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

static char	*extract_word_content(char *str, int *i, t_shell *s)
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
				s->tok->quote = 1;
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

static int	tokenword(t_token **tok, char *str, int *i, t_shell *s)
{
	char	*final_word;
	t_token	*node;

	final_word = extract_word_content(str, i, s);
	if (!final_word)
		return (0);
	node = lstnew_token(s->gc_tmp, final_word, TOKEN_WORD);
	if (!node)
		return (0);
	lstadd_backtok(tok, node);
	return (1);
}

// static int	tokenword(t_token **tok, char *str, int *i, t_shell *s)
// {
// 	char	*final_word;
// 	char	*tmp;
// 	t_token	*node;

// 	final_word = gc_strdup(s->gc_tmp, "");
// 	if (!final_word)
// 		final_word = "";
// 	while (str[*i] && !is_separator(str[*i]))
// 	{
// 		if (str[*i] == '"')
// 			tmp = double_quotes(str, i, s->gc_tmp);
// 		else if (str[*i] == '\'')
// 		{
// 			s->tok->quote = 1;
// 			tmp = single_quote(str, i, s->gc_tmp);
// 		}
// 		else
// 		{
// 			final_word = append_char(s->gc_tmp, final_word, str[(*i)++]);
// 			if (!final_word)
// 				return (0);
// 			continue ;
// 		}
// 		if (!tmp)
// 			return (0);
// 		final_word = gc_strjoin(s->gc_tmp, final_word, tmp);
// 		if (!final_word)
// 			return (0);
// 	}
// 	node = lstnew_token(s->gc_tmp, final_word, TOKEN_WORD);
// 	if (!node)
// 		return (0);
// 	lstadd_backtok(tok, node);
// 	return (1);
// }

int	tokenpipe(t_token **tok, char *str, int *i, t_gc *gc)
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

int	ultime_lexing(t_token **tok, char *str, t_gc *gc, t_shell *s)
{
	int	v;

	v = 0;
	while (str && str[v])
	{
		while (str[v] && (str[v] == ' ' || (str[v] >= 9 && str[v] <= 13)))
			v++;
		if (!str[v])
			break ;
		if (process_token(tok, str, &v, gc))
			continue ;
		if (!tokenword(tok, str, &v, s))
		{
			ft_fprintf(2,
				"bash: syntax error near unexpected token `newline'\n");
			s->exec->last_exit = 2;
			return (0);
		}
	}
	return (1);
}
