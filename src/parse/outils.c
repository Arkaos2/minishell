/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:17:26 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/09 17:37:28 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_array(t_shell *shell, char **old_array, char *new)
{
	size_t	i;
	size_t	size;
	char	**new_array;

	size = 0;
	if (old_array)
	{
		while (old_array[size])
			size++;
	}
	new_array = gc_calloc(shell->gc, sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_array[i] = old_array[i];
		i++;
	}
	new_array[i] = new;
	new_array[i + 1] = NULL;
	return (new_array);
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

void	reset_element(t_shell *shell)
{
	if (shell->gc_tmp)
		gc_destroy(shell->gc_tmp);
	shell->gc_tmp = NULL;
	shell->tok = NULL;
	shell->cmd = NULL;
	shell->exec->cmd_list = NULL;
}
