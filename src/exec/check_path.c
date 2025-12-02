/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:17:54 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/02 18:33:54 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path_list(t_envp *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			if (!env->value || env->value[0] == '\0')
				return (NULL);
			return (ft_split(env->value, ':'));
		}
		env = env->next;
	}
	return (NULL);
}

static char	*try_paths_for_cmd(char **paths, char *cmd, t_gc *gc)
{
	char	*full;
	char	*tmp;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		tmp = gc_strjoin(gc, paths[i], "/");
		if (!tmp)
			return (NULL);
		full = gc_strjoin(gc, tmp, cmd);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		i++;
	}
	return (NULL);
}

int	is_absolute_path(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '/')
		return (1);
	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	return (0);
}

static char	*check_absolute_cmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_envp *env, t_gc *gc)
{
	char	**paths;
	char	*result;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (is_absolute_path(cmd))
		return (check_absolute_cmd(cmd));
	paths = get_path_list(env);
	if (!paths)
		return (NULL);
	result = try_paths_for_cmd(paths, cmd, gc);
	free_split(paths);
	return (result);
}
