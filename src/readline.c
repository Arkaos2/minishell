/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-07 13:17:20 by user              #+#    #+#             */
/*   Updated: 2026-01-07 13:17:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_shell	*init_non_interactive_shell(char **envp)
{
	t_shell	*shell;

	shell = init_struct();
	if (!shell)
		return (NULL);
	shell->gc_tmp = gc_new();
	shell->env = create_envp(shell->gc, envp);
	upgrade_env(shell);
	shell->cmd = init_cmd(shell);
	shell->exec->cmd_list = shell->cmd;
	shell->tok = NULL;
	return (shell);
}

int	process_line_non_interactive(t_shell *shell, char *line)
{
	if (!ultime_lexing(&shell->tok, line, shell->gc_tmp, shell))
		return (0);
	if (shell->tok)
	{
		if (!ultime_filler(shell))
			return (0);
		run_pipes(shell);
	}
	return (1);
}

void	run_non_interactive(char **envp)
{
	t_shell	*shell;
	char	*line;
	size_t	len;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		len = ft_strlen(line);
		if (len && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		shell = init_non_interactive_shell(envp);
		if (!shell)
			return (free(line), (void)0);
		if (!process_line_non_interactive(shell, line))
			reset_element(shell);
		1 && (gc_destroy(shell->gc_tmp), gc_destroy(shell->gc), free(line), 0);
	}
}

int	process_interactive_line(t_shell *shell, char *line)
{
	if (!ultime_lexing(&shell->tok, line, shell->gc_tmp, shell))
		return (0);
	if (!redirs_syntax(shell))
		return (0);
	if (shell->tok)
	{
		if (!ultime_filler(shell))
			return (0);
		run_pipes(shell);
	}
	return (1);
}

int	handle_readline(t_shell *shell, char **line)
{
	// int	ret;

	g_last_signal = 0;
	*line = readline("minishell: ");
	if (!*line)
		return (0);
	if (g_last_signal == 130)
		shell->exec->last_exit = 130;
	if (**line && !is_whitespace(*line))
		add_history(*line);
	// ret = check_syntaxe(*line);
	// if (ret != 1)
	// {
	// 	if (ret == 2)
	// 		shell->exec->last_exit = 2;
	// 	return (-1);
	// }
	return (1);
}
