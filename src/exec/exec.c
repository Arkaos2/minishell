/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:34:53 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/04 16:34:05 by saibelab         ###   ########.fr       */
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

static pid_t	spawn_child(t_exec *exec, int i)
{
	pid_t pid;

	if (i < exec->nb_cmd - 1)
	{
		if (pipe(exec->pipes[i % 2]) == -1)
		{
			perror("pipe");
			cleanup_on_error(exec);
			return (-1);
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		cleanup_on_error(exec);
		return (-1);
	}
	return (pid);
}

static void	handle_parent(t_exec *exec, int i)
{
	if (i > 0)
		if (exec->pipes[(i - 1) % 2][0] >= 0)
			close(exec->pipes[(i - 1) % 2][0]);
	if (i < exec->nb_cmd - 1)
		if (exec->pipes[i % 2][1] >= 0)
			close(exec->pipes[i % 2][1]);
}

void	run_children(t_exec *exec)
{
	t_cmd	*cmd;
	int		i;
	pid_t	pid;

	cmd = exec->cmd_list;
	i = 0;
	while (cmd)
	{
		pid = spawn_child(exec, i);
		if (pid == -1)
			return ;
		cmd->pid = pid;
		if (pid == 0)
			launch_children(cmd, exec, i);
		else
			handle_parent(exec, i);
		cmd = cmd->next;
		i++;
	}
}
