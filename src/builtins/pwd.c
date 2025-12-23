/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:16:27 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/23 16:21:21 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pwd(t_envp *env)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	pwd = get_env_value(env, "PWD");
	if (pwd && ft_strcmp(pwd, cwd) == 0)
		printf("%s\n", pwd);
	else
		printf("%s\n", cwd);
	free(cwd);
	return (0);
}

