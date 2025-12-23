/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:26:18 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/23 16:07:26 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_quotes(t_token **tok, char *str, int *i, t_gc *gc)
{
	int		flag;
	char	*res;
	t_token	*node;

	if (str[*i] != '"')
		return (0);
	(*i)++;
	flag = *i;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (!str[*i])
		return (-1);
	res = ft_substr(str, flag, *i - flag);
	if (!res)
		return (-1);
	node = lstnew_token(gc, res, TOKEN_WORD);
	if (!node)
		return (free(res), -1);
	lstadd_backtok(tok, node);
	free(res);
	if (str[*i] == '"')
		(*i)++;
	return (1);
}

int	single_quote(t_token **tok, char *str, int *i, t_gc *gc)
{
	int		flag;
	char	*res;
	t_token	*node;

	if (str[*i] != '\'')
		return (0);
	(*i)++;
	flag = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (!str[*i])
		return (-1);
	res = ft_substr(str, flag, *i - flag);
	if (!res)
		return (-1);
	node = lstnew_token(gc, res, TOKEN_WORD);
	if (!node)
		return (free(res), -1);
	lstadd_backtok(tok, node);
	free(res);
	if (str[*i] == '\'')
		(*i)++;
	return (1);
}

int	check_syntaxe(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (str[len] == 32 || (str[len] >= 9 && str[len] <= 13))
		len--;
	if (str[len] == '<' || str[len] == '>' || str[len] == '|')
	{
		free(str);
		ft_fprintf(2,
			"minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	handle_quotes(t_token **tok, char *str, int *i, t_shell *s)
{
	int	ref;

	ref = double_quotes(tok, str, i, s->gc);
	if (ref == -1)
		return (-1);
	if (ref == 1)
		return (1);
	ref = single_quote(tok, str, i, s->gc);
	if (ref == -1)
		return (-1);
	if (ref == 1)
	{
		s->tok->quote = 1;
		return (1);
	}
	return (0);
}
