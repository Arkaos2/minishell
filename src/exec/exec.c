/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:34:53 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/05 17:46:52 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_cmd *cmd, t_shell *shell)
{
	char		**envp;
	char		*path;
	struct stat	st;

	if (!cmd || !cmd->args || !cmd->args[0])
		cleanup_on_error(shell);
	envp = env_to_char(shell);
	if (!envp)
		cleanup_on_error(shell);
	if (stat(cmd->args[0], &st) == 0 && (st.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_fprintf(2, "%s: Is a directory\n", cmd->args[0]);
		safe_exit(shell, 126);
	}
	if (stat(cmd->args[0], &st) == 0 && access(cmd->args[0], X_OK) == -1)
	{
		ft_fprintf(2, "%s: Permission denied\n", cmd->args[0]);
		safe_exit(shell, 126);
	}
	path = get_cmd_path(cmd->args[0], shell->env, shell->gc);
	if (!path)
	{
		ft_fprintf(2, "%s: command not found\n", cmd->args[0]);
		safe_exit(shell, 127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		perror(cmd->args[0]);
		safe_exit(shell, 127);
	}
}

static void	launch_children(t_cmd *cmd, t_shell *shell, int i)
{
	int	ret;

	exec_distributor();
	setup_child_fds(cmd, shell, i);
	setup_heredoc_input(shell, cmd);
	close_all_pipes(shell->exec->pipes, shell->exec->nb_cmd);
	if (cmd && cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
		ret = handle_builtin(cmd, shell);
		safe_exit(shell, ret);
	}
	exec_child(cmd, shell);
}

static pid_t	spawn_child(t_shell *shell, int i)
{
	pid_t pid;

	if (i < shell->exec->nb_cmd - 1)
	{
		if (pipe(shell->exec->pipes[i % 2]) == -1)
		{
			perror("pipe");
			cleanup_on_error(shell);
			return (-1);
		}
	}
	char *cwd = getcwd(NULL, 0);
	free(cwd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		cleanup_on_error(shell);
		return (-1);
	}
	return (pid);
}

static void	handle_parent(t_shell *shell, int i)
{
	if (i > 0)
		if (shell->exec->pipes[(i - 1) % 2][0] >= 0)
			close(shell->exec->pipes[(i - 1) % 2][0]);
	if (i < shell->exec->nb_cmd - 1)
		if (shell->exec->pipes[i % 2][1] >= 0)
			close(shell->exec->pipes[i % 2][1]);
}

void	run_children(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;
	pid_t	pid;

	cmd = shell->exec->cmd_list;
	i = 0;
	while (cmd)
	{
		pid = spawn_child(shell, i);
		if (pid == -1)
			return ;
		cmd->pid = pid;
		sig_ignore();
		if (pid == 0)
			launch_children(cmd, shell, i);
		else
		{
			handle_parent(shell, i);
			signal_distributor();
		}
		cmd = cmd->next;
		i++;
	}
}
