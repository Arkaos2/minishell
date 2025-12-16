/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:30:58 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/16 15:34:28 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env(t_envp *env)
{
	int	len;
	
	while (env)
	{
		if (!env->value && ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "\n", 2);
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
