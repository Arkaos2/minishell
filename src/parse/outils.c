/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:17:26 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/06 20:03:59 by pmalumba         ###   ########.fr       */
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
	new_array = gc_calloc(shell->gc_tmp, sizeof(char *) * (size + 2));
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

void	reset_element(t_shell *shell)
{
	gc_destroy(shell->gc_tmp);
	shell->gc_tmp = NULL;
	shell->tok = NULL;
	shell->cmd = NULL;
	shell->exec->cmd_list = NULL;
}
