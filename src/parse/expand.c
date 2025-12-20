/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:09:30 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/20 19:15:39 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollars_conv(t_shell *s, char *name)
{
	int		i;
	char	*res;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (s->envp[i])
	{
		if (!ft_strncmp(s->envp[i], name, len) && s->envp[i][len] == '=')
		{
			res = gc_strdup(s->gc, s->envp[i] + len + 1);
			if (!res)
				return (NULL);
			return (res);
		}
		i++;
	}
	res = gc_strdup(s->gc, "");
	if (!res)
		return (NULL);
	return (res);
}

int	get_var_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

char	*expand_dollars(t_shell *s, char *str)
{
	int		i;
	char	*result;
	int		len;
	char	*name;
	char	*value;
	char	tmp[2];

	i = 0;
	result = gc_strdup(s->gc, "");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				value = ft_itoa(s->status);
				if (!value)
					return (NULL);
				result = gc_strjoin(s->gc, result, value);
				if (!result)
					return (free(value), NULL);
				i += 2;
				continue ;
			}
			i++;
			len = get_var_len(&str[i]);
			name = ft_substr(str, i, len);
			if (!name)
				return (NULL);
			value = dollars_conv(s, name);
			if (!value)
			{
				free(name);
				value = "";
			}
			result = gc_strjoin(s->gc, result, value);
			if (!result)
				return (free(name), NULL);
			i += len;
		}
		else
		{
			tmp[0] = str[i];
			tmp[1] = '\0';
			result = gc_strjoin(s->gc, result, tmp);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}
