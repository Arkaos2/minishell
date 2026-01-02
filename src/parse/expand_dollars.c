/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@example.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:00:00 by automated         #+#    #+#             */
/*   Updated: 2025/12/22 20:00:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollars_conv(t_shell *s, char *name)
{
    t_envp  *tmp;
	char	*res;
	size_t	len;

	len = ft_strlen(name);
    tmp = s->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, name, len))
		{
			res = gc_strdup(s->gc_tmp, tmp->value);
			if (!res)
				return (NULL);
			return (res);
		}
		tmp = tmp->next;
	}
	res = gc_strdup(s->gc_tmp, "");
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

	if (!str)
		return (NULL);
	i = 0;
	result = gc_strdup(s->gc_tmp, "");
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
				result = gc_strjoin(s->gc_tmp, result, value);
				if (!result)
					return (free(value), NULL);
				i += 2;
				continue ;
			}
			i++;
			len = get_var_len(&str[i]);
			name = gc_substr(s->gc_tmp, str, i, len);
			if (!name)
				return (NULL);
			value = dollars_conv(s, name);
			if (!value)
			{
                // return (NULL);
				value = "";
			}
			result = gc_strjoin(s->gc_tmp, result, value);
			if (!result)
				return (NULL);
			i += len;
		}
		else
		{
			tmp[0] = str[i];
			tmp[1] = '\0';
			result = gc_strjoin(s->gc_tmp, result, tmp);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}