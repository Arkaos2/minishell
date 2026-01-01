/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-25 13:19:32 by user              #+#    #+#             */
/*   Updated: 2025-12-25 13:19:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;
	int i;

	i = 0;
	if (!cmd->args[1])
	{
		write(STDOUT_FILENO, "exit\n", 5);
		safe_exit(shell->gc, shell->exec->last_exit);
	}
	else if (cmd->args[2])
		return (write(STDERR_FILENO, "exit: too many arguments\n", 25), 1);
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			write(STDERR_FILENO, "exit: numeric argument required\n", 32);
			write(STDOUT_FILENO, "exit\n", 5);
			safe_exit(shell->gc,2);
		}
		i++;
	}
	exit_code = ft_atoi(cmd->args[1]);
	write(STDOUT_FILENO, "exit\n", 5);
	safe_exit(shell->gc, exit_code);
	return (0);
}
