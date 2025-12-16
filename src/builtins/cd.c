/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:39:04 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/16 18:56:13 by saibelab         ###   ########.fr       */
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
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			env->value = gc_strdup(gc, value);
			return;
		}
		env = env->next;
	}
}

void	handle_cd(t_cmd *cmd, t_envp *env, t_gc *gc)
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
		return;
	}

	newpwd = getcwd(NULL, 0);

	update_env(env, "OLDPWD", oldpwd, gc);
	update_env(env, "PWD", newpwd, gc);
	printf("CD EXEC PID = %d\n", getpid());
	free(oldpwd);
	free(newpwd);
}


