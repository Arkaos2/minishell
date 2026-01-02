/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:17:26 by pmalumba          #+#    #+#             */
/*   Updated: 2026/01/02 17:53:22 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **av)
{
	int	v;

	if (!av || !av[0])
		return ;
	v = 0;
	while (av[v])
		free(av[v++]);
	free(av);
	av = NULL;
}

char **fill_array(t_shell *shell, char **old_array, char *new)
{
    size_t     i;
    size_t     size;
    char    **new_array;

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

char	**dup_map(char **src, int height)
{
	char	**copy;
	int		i;

	if (!src || !src[0] || height <= 0)
		return (NULL);
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
			return (free_split(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
