/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:26:18 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/20 17:31:10 by pmalumba         ###   ########.fr       */
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
