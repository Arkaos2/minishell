/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:10:38 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/08 16:30:35 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *flag)
{
	int	i;

	i = 0;
	if (!flag || !flag[i])
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

static int	skip_n(char **args, int *flag)
{
	int	i;

	i = 1;
	*flag = 0;
	while (args[i] && check_flag(args[i]))
	{
		*flag = 1;
		i++;
	}
	return (i);
}

int	handle_echo(t_cmd *cmd)
{
	int	flag;
	int	i;
	int	len;

	i = skip_n(cmd->args, &flag);
	while (cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);
		write(STDOUT_FILENO, cmd->args[i], len);
		if (cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
