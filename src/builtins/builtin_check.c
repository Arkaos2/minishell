/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:03:02 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/23 17:12:44 by saibelab         ###   ########.fr       */
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

int	handle_builtin(t_cmd *cmd, t_shell *shell)
{
	if (strcmp(cmd->args[0], "echo") == 0)
		return (handle_echo(cmd));
	else if (strcmp(cmd->args[0], "cd") == 0)
		return (handle_cd(cmd, shell->env, shell->gc));
	else if (strcmp(cmd->args[0], "exit") == 0)
		return (handle_exit(cmd, shell));
	else if (strcmp(cmd->args[0], "env") == 0)
		return (handle_env(shell->env, 0));
	else if (strcmp(cmd->args[0], "export") == 0)
		return (handle_export(cmd, shell->env, shell->gc));
	else if (strcmp(cmd->args[0], "unset") == 0)
		return (handle_unset(cmd, shell->env, shell->gc));
	else if (strcmp(cmd->args[0], "pwd") == 0)
		return (handle_pwd(shell->env));
	return (0);
}
