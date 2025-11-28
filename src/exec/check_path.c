/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:55:25 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/28 17:27:29 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **envp)
{
	int		i;
	char	*path_value;
	char	**paths;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_value = envp[i] + 5;
	if (!path_value || path_value[0] == '\0')
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*try_paths_for_cmd(char **paths, char **cmd)
{
	char	*tmp;
	char	*correct;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			break ;
		correct = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (!correct)
			break ;
		if (access(correct, X_OK) == 0)
			return (correct);
		free(correct);
		i++;
	}
	return (NULL);
}

int	is_absolute_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	return (0);
}

char	*check_absolute_path(char **cmd, char *infile)
{
	char	*result;

	if (access(cmd[0], X_OK) == 0)
		result = ft_strdup(cmd[0]);
	else
	{
		if (access(infile, R_OK) == 0)
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		result = NULL;
	}
	return (result);
}

char	*search_in_path(char **cmd, char **envp, char *infile)
{
	char	**paths;
	char	*result;

	paths = get_path(envp);
	if (!paths)
		return (NULL);
	result = try_paths_for_cmd(paths, cmd);
	if (!result && access(infile, R_OK) == 0)
	{
		ft_putstr_fd("pipex : ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	free_split(paths);
	return (result);
}
