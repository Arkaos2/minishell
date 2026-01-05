/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:10:38 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/31 15:31:26 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_newline(char *flag)
{
	int	i;

	i = 0;
	if (!flag)
		return (0);
	if (flag[i] != '-')
		return (0);
	i++;
	while (flag[i] == 'n')
		i++;
	if (flag[i])
		return (0);
	return (1);
}

int	handle_echo(t_cmd *cmd)
{
	int	flag;
	int i;
	int len;

	if (cmd->args[1] && check_newline(cmd->args[1]))
	{
		i = 2;
		flag = 1;
	}
	else
	{
		i = 1;
		flag = 0;
	}
	while(cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);
		write(STDOUT_FILENO, cmd->args[i], len);
		// if (cmd->args[i + 1])
		// 	write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
