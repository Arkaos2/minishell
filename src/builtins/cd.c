/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:39:04 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/23 16:21:14 by saibelab         ###   ########.fr       */
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

int	handle_cd(t_cmd *cmd, t_envp *env, t_gc *gc)
{
	char	*oldpwd;
	char	*newpwd;
	char	*path;

	oldpwd = getcwd(NULL, 0);
	if (!cmd->args[1])
		path = get_env_value(env, "HOME");
	else
		path = cmd->args[1];
	if (!path || chdir(path) != 0)
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


