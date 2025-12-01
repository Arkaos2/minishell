/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:34:53 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/01 18:41:26 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_stdin(t_cmd *cmd, t_exec *exec, int i)
{
	int	fd;

	if (i == 0 && cmd->infile)
{
	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->infile);
		exit(127);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

	else if (i > 0)
		dup2(exec->pipes[i - 1][0], STDIN_FILENO);
}

static void	setup_child_stdout(t_cmd *cmd, t_exec *exec, int i)
{
	int	fd;
	int	flags;

	if (i == exec->nb_cmd - 1 && cmd->outfile)
	{
		flags = O_CREAT;
		flags += O_WRONLY;
		if (cmd->append == 1)
			flags += O_APPEND;
		else
			flags += O_TRUNC;
		fd = open(cmd->outfile, flags, 0644);
		if (fd < 0)
		{
			perror(cmd->outfile);
			exit(1);
		}
		if (fd >= 0)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	else if (i < exec->nb_cmd - 1)
		dup2(exec->pipes[i][1], STDOUT_FILENO);
}

void	setup_child_fds(t_cmd *cmd, t_exec *exec, int i)
{
	setup_child_stdin(cmd, exec, i);
	setup_child_stdout(cmd, exec, i);
}

void	exec_child(t_cmd *cmd, t_exec *exec)
{
	char	**envp;
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	envp = env_to_char(exec->env);
	if (!envp)
		exit(127);
	path = get_cmd_path(cmd->args[0], exec->env);
	if (!path)
	{
		ft_fprintf(2, "%s: command not found\n", cmd->args[0]);
		exit(127);
	}
	execve(path, cmd->args, envp);
	perror(cmd->args[0]);
	exit(127);
}


static void	run_children(t_exec *exec)
{
	t_cmd	*cmd;
	int		i;
	pid_t	pid;

	i = 0;
	cmd = exec->cmd_list;
	while (cmd)
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			setup_child_fds(cmd, exec, i);
			close_all_pipes(exec->pipes, exec->nb_cmd);
			exec_child(cmd, exec);
		}
		cmd = cmd->next;
		i++;
	}
}

void	run_pipes(t_exec *exec)
{
	int	i;
	int	status;

	exec->nb_cmd = count_cmds(exec->cmd_list);
	exec->pipes = create_pipes(exec->nb_cmd, exec->gc);
	if (!exec->pipes && exec->nb_cmd > 1)
	{
		perror("pipe");
		return;
	}
	run_children(exec);
	close_all_pipes(exec->pipes, exec->nb_cmd);
	i = 0;
	exec->last_exit = 0;
	while (i < exec->nb_cmd)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			exec->last_exit = WEXITSTATUS(status);
		i++;
	}
		exec->pipes = NULL;
}
