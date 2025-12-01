/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:39:11 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/01 19:58:11 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->limiter)
			free(cmd->limiter);
		free(cmd);
		cmd = tmp;
	}
}

void	free_envp(t_envp *env)
{
	t_envp	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	free_cmds(exec->cmd_list);
	if (exec->pipes)
		free_pipes(exec->pipes, exec->nb_cmd);
	free_envp(exec->env);
	free(exec);
}
