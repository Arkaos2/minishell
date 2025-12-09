/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:30:00 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/09 18:51:08 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_gc	*gc;
	t_exec	*exec;
	t_cmd	*c1;
	t_redir	*r1;


	(void)argc;
	(void)argv;

	/* Init GC et exec */
	gc = gc_new();
	if (!gc)
		return (1);
	exec = gc_calloc(gc, sizeof(*exec));

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


	/* Chaînage dans l'ordre Bash */
	r1->next = NULL;  // EOF1 -> EOF2
	c1->redirs = r1;

	/* Chaînage commande unique */
	c1->next = NULL;

	/* Remplissage des heredocs */
	signal(SIGINT, heredoc_sigint_handler);
	fill_all_heredocs(gc, c1);
	signal(SIGINT, SIG_DFL);

	/* Setup exec structure */
	exec->cmd_list = c1;
	exec->env = create_envp(gc, envp);
	exec->pipes = NULL;
	exec->nb_cmd = count_cmds(c1);
	exec->last_exit = 0;
	exec->gc = gc;

	/* Execution mock (juste un pipe simple pour test) */
	run_children(exec);

	gc_destroy(gc);
	return (0);
}
