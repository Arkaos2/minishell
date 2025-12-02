/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:25:09 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/02 19:28:51 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_gc	*gc;
	t_exec	*exec;
	t_cmd	*c1;
	t_cmd	*c2;
	t_cmd	*c3;
	t_redir	*r;

	(void)argc;
	(void)argv;

	/* Initialisation GC */
	gc = gc_new();
	if (!gc)
		return (1);

	/* Allocation exec et commandes */
	exec = gc_calloc(gc, sizeof(*exec));
	c1 = gc_calloc(gc, sizeof(*c1));
	c2 = gc_calloc(gc, sizeof(*c2));
	c3 = gc_calloc(gc, sizeof(*c3));
	if (!exec || !c1 || !c2 || !c3)
		return (1);

	/* ------------------------------ */
	/* Commande 1 : cat < infile      */
	/* ------------------------------ */
	c1->args = gc_calloc(gc, 2 * sizeof(char *));
	c1->args[0] = gc_strdup(gc, "cat");
	c1->args[1] = NULL;

	r = gc_calloc(gc, sizeof(*r));
	r->type = R_IN;
	r->file = gc_strdup(gc, "infile");
	r->next = NULL;
	c1->redirs = r;

	/* ------------------------------ */
	/* Commande 2 : grep gc > out.txt */
	/* ------------------------------ */
	c2->args = gc_calloc(gc, 3 * sizeof(char *));
	c2->args[0] = gc_strdup(gc, "grep");
	c2->args[1] = gc_strdup(gc, "gc");
	c2->args[2] = NULL;

	r = gc_calloc(gc, sizeof(*r));
	r->type = R_OUT;
	r->file = gc_strdup(gc, "out.txt");
	r->next = NULL;
	c2->redirs = r;

	/* ------------------------------ */
	/* Commande 3 : wc -l >> final.txt */
	/* ------------------------------ */
	c3->args = gc_calloc(gc, 3 * sizeof(char *));
	c3->args[0] = gc_strdup(gc, "wc");
	c3->args[1] = gc_strdup(gc, "-l");
	c3->args[2] = NULL;

	r = gc_calloc(gc, sizeof(*r));
	r->type = R_APPEND;
	r->file = gc_strdup(gc, "final.txt");
	r->next = NULL;
	c3->redirs = r;

	/* Chaînage */
	c1->next = c2;
	c2->next = c3;
	c3->next = NULL;

	/* Setup exec */
	exec->cmd_list = c1;
	exec->env = create_envp(gc, envp);
	exec->pipes = NULL;
	exec->nb_cmd = count_cmds(c1);
	exec->last_exit = 0;
	exec->gc = gc;

	/* Exécution du pipeline */
	if (!check_redirs(exec->cmd_list))
	{
		gc_destroy(gc);
		return (1);
	}

	run_pipes(exec);

	/* Cleanup */
	gc_destroy(gc);
	return (0);
}
