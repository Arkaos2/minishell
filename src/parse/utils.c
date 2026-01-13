/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:48:59 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/13 15:49:51 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (1);
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	*append_char(t_gc *gc, char *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	if (!str)
		return (NULL);
	while (str[len])
		len++;
	new_str = gc_calloc(gc, sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
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
