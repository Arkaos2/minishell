/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:08:55 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/02 16:08:55 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;
	int	i;

	if (!cmd->args[1])
	{
		write(STDOUT_FILENO, "exit\n", 5);
		safe_exit(shell, shell->exec->last_exit);
	}
	i = 0;
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]) && !(i == 0
			&& (cmd->args[1][i] == '+' || cmd->args[1][i] == '-')))
		{
			write(STDERR_FILENO, "exit: numeric argument required\n", 32);
			write(STDOUT_FILENO, "exit\n", 5);
			safe_exit(shell, 2);
		}
		i++;
	}
	if (cmd->args[2])
		return (write(STDERR_FILENO, "exit: too many arguments\n", 25), 1);
	exit_code = ft_atoi(cmd->args[1]);
	write(STDOUT_FILENO, "exit\n", 5);
	return (safe_exit(shell, exit_code), 0);
}
