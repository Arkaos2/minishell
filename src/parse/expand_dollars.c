/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@example.com>                 +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:00:00 by automated         #+#    #+#             */
/*   Updated: 2025/12/22 20:00:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key_dollars(t_shell *s, char *name)
{
	t_envp	*tmp;
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

int	key_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

static char	*handle_status(t_shell *s, char *result, int *i)
{
	char	*val;
	char	*new_res;

	val = ft_itoa(s->status);
	if (!val)
		return (NULL);
	new_res = gc_strjoin(s->gc_tmp, result, val);
	free(val);
	if (!new_res)
		return (NULL);
	*i += 2;
	return (new_res);
}

static char	*handle_variable(t_shell *s, char *str, char *result, int *i)
{
	int		len;
	char	*name;
	char	*val;
	char	*new_res;

	(*i)++;
	len = key_len(&str[*i]);
	name = gc_substr(s->gc_tmp, str, *i, len);
	if (!name)
		return (NULL);
	val = key_dollars(s, name);
	if (!val)
		val = "";
	new_res = gc_strjoin(s->gc_tmp, result, val);
	if (!new_res)
		return (NULL);
	*i += len;
	return (new_res);
}

char	*expand_dollars(t_shell *s, char *str)
{
	int		i;
	char	*res;
	char	tmp[2];

	i = 0;
	res = gc_strdup(s->gc_tmp, "");
	if (!res)
		return (NULL);
	while (res && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			res = handle_status(s, res, &i);
		else if (str[i] == '$' && str[i + 1])
			res = handle_variable(s, str, res, &i);
		else
		{
			tmp[0] = str[i++];
			tmp[1] = '\0';
			res = gc_strjoin(s->gc, res, tmp);
			if (!res)
				return (NULL);
		}
	}
	return (res);
}

// char	*expand_dollars(t_shell *s, char *str)
// {
// 	int		i;
// 	char	*result;
// 	int		len;
// 	char	*name;
// 	char	*value;
// 	char	tmp[2];

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	result = gc_strdup(s->gc, "");
// 	if (!result)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			if (str[i + 1] == '?')
// 			{
// 				value = ft_itoa(s->status);
// 				if (!value)
// 					return (NULL);
// 				result = gc_strjoin(s->gc, result, value);
// 				if (!result)
// 					return (free(value), NULL);
// 				i += 2;
// 				continue ;
// 			}
// 			i++;
// 			len = key_len(&str[i]);
// 			name = gc_substr(s->gc, str, i, len);
// 			if (!name)
// 				return (NULL);
// 			value = key_dollars(s, name);
// 			if (!value)
// 				value = "";
// 			result = gc_strjoin(s->gc, result, value);
// 			if (!result)
// 				return (NULL);
// 			i += len;
// 		}
// 		else
// 		{
// 			tmp[0] = str[i];
// 			tmp[1] = '\0';
// 			result = gc_strjoin(s->gc, result, tmp);
// 			if (!result)
// 				return (NULL);
// 			i++;
// 		}
// 	}
// 	return (result);
// }
