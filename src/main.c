/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:30:00 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/10 19:57:50 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_gc	*gc;
	t_exec	*exec;
	t_cmd	*c1;
	t_shell *shell;
	t_redir	*r1;


	(void)argc;
	(void)argv;

	/* Init GC et exec */
	gc = gc_new();
	if (!gc)
		return (1);
	exec = gc_calloc(gc, sizeof(*exec));
	if (!exec)
		return (1);
	shell = gc_calloc(gc, sizeof(*shell));
	if (!shell)
		return (1);

	/* Commande 1 : cat << EOF1 << EOF2 */
	c1 = gc_calloc(gc, sizeof(*c1));
	c1->args = gc_calloc(gc, 2 * sizeof(char *));
	c1->args[0] = gc_strdup(gc, "cat");
	c1->args[1] = NULL;

	/* Heredoc EOF1 */
	r1 = gc_calloc(gc, sizeof(*r1));
	r1->type = R_HEREDOC;
	r1->file = gc_strdup(gc, "EOF1");
	r1->heredoc_content = NULL;

	r1->next = NULL;
	c1->redirs = r1;

	c1->next = NULL;

	/* wire shell early so we use shell->exec everywhere */
	shell->exec = exec;
	shell->tokx = NULL;
	shell->cmd = c1;
	shell->gc = gc;

	shell->exec->cmd_list = c1;
	shell->exec->env = create_envp(gc, envp);
	shell->exec->pipes = NULL;
	shell->exec->nb_cmd = count_cmds(c1);
	shell->exec->last_exit = 0;

	shell->envp = shell->exec->env;

	fill_all_heredocs(shell);

	run_children(shell);

	gc_destroy(gc);
	return (0);
}
