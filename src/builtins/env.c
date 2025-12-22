/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:30:58 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/22 17:17:05 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_envp *env)
{
	int	len;

	while (env)
	{
		if (!env->value && ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "=", 1);
			len = ft_strlen(env->value);
			write(STDOUT_FILENO, env->value, len);
			write(STDOUT_FILENO, "\n", 1);
		}
		env = env->next;
	}
}

static void	print_export(t_envp *env)
{
	int	len;

	while (env)
	{
		if (!env->value && ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, "export ", 7);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, "export ", 7);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "=", 1);
			len = ft_strlen(env->value);
			write(STDOUT_FILENO, env->value, len);
			write(STDOUT_FILENO, "\n", 1);
		}
		env = env->next;
	}
}

int	handle_env(t_envp *env, int flag)
{
	if(flag == 1)
		print_export(env);
	else
		print_env(env);

}
