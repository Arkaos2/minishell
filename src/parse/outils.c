/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:17:26 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/01 18:08:43 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_list(t_cmd *cmd, char *av)
{
	int	v;
	if (!av)
		return (0);
	cmd->args = ft_split(av, ' ');
	if (!cmd->args)
		return (0);
	v = 0;
	
	return (1);
}

void	free_array(char **av)
{
	int	v;

	if (!av || !av[0])
		return ;
	v = 0;
	while (av[v])
		free(av[v++]);
	free(av);
	av = NULL;
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
