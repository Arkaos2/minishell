/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibHITCHENS <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:30:46 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/17 17:04:43 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	shell->exec = gc_calloc(gc, sizeof(t_exec));
	if (!shell->exec)
		return (NULL);
	shell->exec->cmd_list = shell->cmd;
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
	shell = init_struct();
    if (!shell)
        return (1);
    shell->env = create_envp(shell->gc, envp);

    while (1)
    {
        line = readline("minishell: ");
        if (!line)
            break;

        if (*line && !is_whitespace(line))
            add_history(line);

		/* prepare a fresh command structure for this input */
		shell->tok = NULL;
		shell->cmd = gc_calloc(shell->gc, sizeof(t_cmd));
		if (!shell->cmd)
		{
			perror("gc_calloc");
			free(line);
			continue;
		}
		shell->cmd->args = gc_calloc(shell->gc, sizeof(char *) * 100);
		if (!shell->cmd->args)
		{
			perror("gc_calloc");
			free(line);
			continue;
		}
		shell->exec->cmd_list = shell->cmd;
        ultime_lexing(&shell->tok, line, shell->gc);
        if (shell->tok)
        {
            ultime_filler(shell);
            shell->exec->cmd_list = shell->cmd;
            run_pipes(shell); // builtins modifient le bon env et cwd
        }

        free(line);
        // ❌ PAS DE gc_destroy ICI
    }
    gc_destroy(shell->gc); // ✅ UNE SEULE FOIS
    return (0);
}


