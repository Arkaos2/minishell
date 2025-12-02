/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:34:53 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/02 18:23:05 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_cmd *cmd, t_exec *exec)
{
	char	**envp;
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		cleanup_on_error(exec);
	envp = env_to_char(exec->gc, exec->env);
	if (!envp)
		cleanup_on_error(exec);
	path = get_cmd_path(cmd->args[0], exec->env, exec->gc);
	if (!path)
	{
		ft_fprintf(2, "%s: command not found\n", cmd->args[0]);
		safe_exit(exec, 127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		perror(cmd->args[0]);
		safe_exit(exec, 127);
	}
}

static void	launch_children(t_cmd *cmd, t_exec *exec, int i)
{
	setup_child_fds(cmd, exec, i);
	close_all_pipes(exec->pipes, exec->nb_cmd);
	exec_child(cmd, exec);
}

static void	run_children(t_exec *exec)
{
	t_cmd	*cmd;
	int		i;
	pid_t	pid;

	cmd = exec->cmd_list;
	i = 0;
	while (cmd)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			cleanup_on_error(exec);
		}
		cmd->pid = pid;
		if (pid == 0)
			launch_children(cmd, exec, i);
		else
		{
			if (i > 0)
				close(exec->pipes[i - 1][0]);
			if (i < exec->nb_cmd - 1)
				close(exec->pipes[i][1]);
		}
		cmd = cmd->next;
		i++;
	}
}

void	run_pipes(t_exec *exec)
{
	int		status;
	t_cmd	*cmd;

	exec->nb_cmd = count_cmds(exec->cmd_list);
	exec->pipes = create_pipes(exec->nb_cmd, exec->gc);
	if (!exec->pipes && exec->nb_cmd > 1)
		cleanup_on_error(exec);
	if (!exec->pipes && exec->nb_cmd > 1)
	{
		perror("pipe");
		return ;
	}
	run_children(exec);
	close_all_pipes(exec->pipes, exec->nb_cmd);
	cmd = exec->cmd_list;
	exec->last_exit = 0;
	while (cmd)
	{
		if (waitpid(cmd->pid, &status, 0) > 0)
			if (WIFEXITED(status))
				exec->last_exit = WEXITSTATUS(status);
		cmd = cmd->next;
	}
	exec->pipes = NULL;
}
