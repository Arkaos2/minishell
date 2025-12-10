/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:30:46 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/08 21:05:24 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_struct(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->gc = gc_new();
	if (!cmd->gc)
		return (free(cmd), NULL);
	cmd->args = gc_calloc(cmd->gc, sizeof(char *) * 100);
	if (!cmd->args)
		return (gc_destroy(cmd->gc), free(cmd), NULL);
	cmd->redirs = NULL;
	cmd->tok = NULL;
	return (cmd);
}

int	main(int ac, char **av)
{
	t_cmd	*cmd;

	if (ac != 2)
		return (0);
	cmd = init_struct();
	if (!cmd)
	{
		perror("init_strut");
		exit(ENOMEM);
	}
	ultime_lexing(&cmd->tok, av[1], cmd->gc);
	puts("=====TOKEN======");
	t_token *tmp;
	tmp = cmd->tok;
	while (tmp)
	{
		printf("[%u] %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	ultime_filler(cmd);
	puts("=====REDIRS======");
	for (size_t i = 0; cmd->args[i]; i++)
	{
		printf("arg[%zu] = %s\n", i, cmd->args[i]);
	}
	while (cmd->redirs)
	{
		printf("\n[%u] %s\n", cmd->redirs->type, cmd->redirs->file);
		cmd->redirs = cmd->redirs->next;
	}
	gc_destroy(cmd->gc);
	free(cmd);
	return (1);
}
