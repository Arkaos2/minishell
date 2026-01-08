#include "minishell.h"


static char	*validate_path(char *cmd, t_shell *shell)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && (st.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_fprintf(2, "%s: Is a directory\n", cmd);
		safe_exit(shell, 126);
	}
	if (stat(cmd, &st) != 0)
	{
		if (errno == ENOTDIR)
		{
			ft_fprintf(2, "%s: Not a directory\n", cmd);
			safe_exit(shell, 126);
		}
		ft_fprintf(2, "%s: No such file or directory\n", cmd);
		safe_exit(shell, 127);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_fprintf(2, "%s: Permission denied\n", cmd);
		safe_exit(shell, 126);
	}
	return (cmd);
}

static char	*get_executable_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (is_absolute_path(cmd->args[0]))
		return (validate_path(cmd->args[0], shell));
	path = get_cmd_path(cmd->args[0], shell->env, shell->gc);
	if (!path)
	{
		ft_fprintf(2, "%s: command not found\n", cmd->args[0]);
		safe_exit(shell, 127);
	}
	return (path);
}

void	exec_child(t_cmd *cmd, t_shell *shell)
{
	char	**envp;
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		cleanup_on_error(shell);
	envp = env_to_char(shell);
	if (!envp)
		cleanup_on_error(shell);
	path = get_executable_path(cmd, shell);
	if (execve(path, cmd->args, envp) == -1)
	{
		perror(cmd->args[0]);
		safe_exit(shell, 127);
	}
}
