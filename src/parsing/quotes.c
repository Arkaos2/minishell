/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:26:18 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/16 17:41:06 by pmalumba         ###   ########.fr       */
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
	res = ft_substr(str, flag, *i - flag);
	if (!res)
		return (0);
	node = lstnew_token(gc, res, TOKEN_WORD);
	if (!node)
		return (free(res), 0);
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
	res = ft_substr(str, flag, *i - flag);
	if (!res)
		return (0);
	node = lstnew_token(gc, res, TOKEN_WORD);
	if (!node)
		return (free(res), 0);
	lstadd_backtok(tok, node);
	free(res);
	if (str[*i] == '\'')
		(*i)++;
	return (1);
}
