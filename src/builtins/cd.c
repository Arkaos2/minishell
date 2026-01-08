/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:39:04 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/02 15:57:47 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_envp *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env(t_envp *env, char *key, char *value, t_gc *gc)
{
	t_envp	*new;

	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (value == NULL)
				env->value = NULL;
			else
				env->value = gc_strdup(gc, value);
			return;
		}
		if (!env->next)
			break;
		env = env->next;
	}
	new = gc_calloc(gc, sizeof(t_envp));
	new->key = gc_strdup(gc, key);
	if (value == NULL)
		new->value = NULL;
	else
		new->value = gc_strdup(gc, value);
	new->next = NULL;
	env->next = new;
}

static char	*get_cd_path(t_cmd *cmd, t_envp *env)
{
	char	*path;

	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		path = get_env_value(env, "HOME");
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = get_env_value(env, "OLDPWD");
		if (!path)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
			return (NULL);
		}
		write(STDOUT_FILENO, path, ft_strlen(path));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
		path = cmd->args[1];
	return (path);
}

int	handle_cd(t_cmd *cmd, t_envp *env, t_gc *gc)
{
	char	*oldpwd;
	char	*newpwd;
	char	*path;

	if (cmd->args[1] && ft_strcmp(cmd->args[1], "--") == 0)
		return (0);
	oldpwd = getcwd(NULL, 0);
	path = get_cd_path(cmd, env);
	if (!path)
	{
		free(oldpwd);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	update_env(env, "OLDPWD", oldpwd, gc);
	update_env(env, "PWD", newpwd, gc);
	free(oldpwd);
	free(newpwd);
	return (0);
}


