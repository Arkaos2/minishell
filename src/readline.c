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
	g_last_signal = 0;
	*line = readline("minishell: ");
	if (!*line)
		return (0);
	if (g_last_signal == 130)
		shell->exec->last_exit = 130;
	if (**line && !is_whitespace(*line))
		add_history(*line);
	return (1);
}
