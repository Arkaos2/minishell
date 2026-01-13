/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:26:18 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/13 17:47:29 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*double_quotes(char *str, int *i, t_gc *gc)
{
	int		flag;
	char	*res;

	if (str[*i] != '"')
		return (NULL);
	(*i)++;
	flag = *i;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (!str[*i])
		return (NULL);
	res = gc_substr(gc, str, flag, *i - flag);
	if (!res)
		return (NULL);
	(*i)++;
	return (res);
}

char	*single_quote(char *str, int *i, t_gc *gc)
{
	int		flag;
	char	*res;

	if (str[*i] != '\'')
		return (NULL);
	(*i)++;
	flag = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (!str[*i])
		return (NULL);
	res = gc_substr(gc, str, flag, *i - flag);
	if (!res)
		return (NULL);
	(*i)++;
	return (res);
}

int	check_syntaxe(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str) - 1;
	while (len >= 0 && (str[len] == ' ' || (str[len] >= 9 && str[len] <= 13)))
		len--;
	if (len < 0)
		return (1);
	if (str[len] == '<' || str[len] == '>' || str[len] == '|')
	{
		free(str);
		ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n");
		return (2);
	}
	return (1);
}
