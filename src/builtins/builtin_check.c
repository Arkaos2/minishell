/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:03:02 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/12 17:58:53 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	int			i;
	const char	*builtins[] = {
		"cd",
		"echo",
		"exit",
		"env",
		"pwd",
		"unset",
		"export",
		NULL
	};

	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	handle_builtin(t_cmd *cmd, t_envp *env)
{
	if (strcmp(cmd->args[0], "echo") == 0)
		handle_echo(cmd);
	// else if (strcmp(cmd->args[0], "cd") == 0)
	// 	handle_cd(cmd, exec);
	// else if (strcmp(cmd->args[0], "exit") == 0)
	// 	handle_exit(cmd, exec);
	else if (strcmp(cmd->args[0], "env") == 0)
		handle_env(env);
// 	else if (strcmp(cmd->args[0], "export") == 0)
// 		handle_export(cmd, exec);
// 	else if (strcmp(cmd->args[0], "unset") == 0)
// 		handle_unset(cmd, exec);
// 	else if (strcmp(cmd->args[0], "pwd") == 0)
// 		handle_pwd(cmd, exec);
//
}
