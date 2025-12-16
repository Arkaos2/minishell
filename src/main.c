/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:30:46 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/16 15:07:10 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* debug removed */

static t_shell	*init_struct(void)
{
	t_shell	*shell;
	t_gc	*gc;

	gc = gc_new();
	if (!gc)
		return (NULL);
	shell = gc_calloc(gc, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cmd = gc_calloc(gc, sizeof(t_cmd));
	if (!shell->cmd)
		return (NULL);
	shell->cmd->args = gc_calloc(gc, sizeof(char *) * 100);
	if (!shell->cmd->args)
		return (NULL);

	/* allocate exec structure used by the rest of the engine */
	shell->exec = gc_calloc(gc, sizeof(t_exec));
	if (!shell->exec)
		return (NULL);
	shell->exec->cmd_list = shell->cmd;
	shell->exec->env = NULL;
	shell->exec->pipes = NULL;
	shell->exec->nb_cmd = 0;
	shell->exec->last_exit = 0;

	shell->gc = gc;
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell *shell;
	(void)argc;
	(void)argv;

	if (!isatty(STDIN_FILENO))
	{
		char *gline;
		while ((gline = get_next_line(STDIN_FILENO)) != NULL)
		{
			size_t len = ft_strlen(gline);
			if (len > 0 && gline[len - 1] == '\n')
				gline[len - 1] = '\0';
			if (*gline == '\0')
			{
				free(gline);
				continue;
			}
			shell = init_struct();
			if (!shell)
			{
				perror("init_struct");
				free(gline);
				continue;
			}
			shell->env = create_envp(shell->gc, envp);
			shell->exec->env = shell->env;
			shell->tok = NULL;
			ultime_lexing(&shell->tok, gline, shell->gc);
			if (shell->tok)
			{
				ultime_filler(shell);
				shell->exec->cmd_list = shell->cmd;
				run_pipes(shell);
			}
			gc_destroy(shell->gc);
			free(gline);
		}
		return (0);
	}
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break;
		if (*line && !is_whitespace(line))
			add_history(line);
		shell = init_struct();
		if (!shell)
		{
			perror("init_struct");
			free(line);
			continue;
		}
	shell->env = create_envp(shell->gc, envp);
	shell->exec->env = shell->env;
		shell->tok = NULL;
		ultime_lexing(&shell->tok, line, shell->gc);
		if (!shell->tok)
		{
			gc_destroy(shell->gc);
			free(line);
			continue;
		}
		ultime_filler(shell);
	shell->exec->cmd_list = shell->cmd;
	run_pipes(shell);
	gc_destroy(shell->gc);
	free(line);
	}
	return (0);
}


