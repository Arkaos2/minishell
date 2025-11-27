/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:17:26 by pmalumba          #+#    #+#             */
/*   Updated: 2025/11/27 19:54:47 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_list(t_cmd *cmd, char *av)
{
	if (!av)
		return (0);
	cmd->args = ft_split(av, ' ');
	if (!cmd->args)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_cmd *cmd;

	(void)ac;
	cmd = init_cmd();
	if (add_list(cmd, av[1]))
	{
		for (size_t i = 0; cmd->args[i]; i++)
			printf("args[%zu] = %s\n", i, cmd->args[i]);
		return (0);
	}
	return (1);
}