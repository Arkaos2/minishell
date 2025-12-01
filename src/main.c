#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_exec	*exec;
	t_envp	*env;
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	t_cmd	*cmd3;
	t_gc	*gc;

	(void)argc;
	(void)argv;

	// Allocation des structures via GC
	gc = gc_new();
	cmd1 = gc_calloc(gc, sizeof(t_cmd));
	cmd2 = gc_calloc(gc, sizeof(t_cmd));
	cmd3 = gc_calloc(gc, sizeof(t_cmd));
	exec = gc_calloc(gc, sizeof(t_exec));
	if (!cmd1 || !cmd2 || !cmd3 || !exec || !gc)
		return (1);

	// Création de l'environnement
	env = create_envp(gc, envp);

	// Commande 1 : cat < infile
	cmd1->args = gc_calloc(gc, 2 * sizeof(char *));
	cmd1->args[0] = gc_strdup(gc, "cat");
	cmd1->args[1] = NULL;
	cmd1->infile = gc_strdup(gc, "infile");  // redirection d'entrée
	cmd1->outfile = NULL;                     // pas de sortie ici
	cmd1->append = 0;
	cmd1->next = cmd2;

	// Commande 2 : grep gc
	cmd2->args = gc_calloc(gc, 3 * sizeof(char *));
	cmd2->args[0] = gc_strdup(gc, "grep");
	cmd2->args[1] = gc_strdup(gc, "gc");
	cmd2->args[2] = NULL;
	cmd2->infile = NULL;                      // prend l'entrée du pipe
	cmd2->outfile = NULL;                     // pas de redirection ici
	cmd2->append = 0;
	cmd2->next = cmd3;

	// Commande 3 : wc -l > out.txt
	cmd3->args = gc_calloc(gc, 3 * sizeof(char *));
	cmd3->args[0] = gc_strdup(gc, "wc");
	cmd3->args[1] = gc_strdup(gc, "-l");
	cmd3->args[2] = NULL;
	cmd3->infile = NULL;                      // prend l'entrée du pipe
	cmd3->outfile = gc_strdup(gc, "out.txt"); // redirection de sortie
	cmd3->append = 0;                         // écrase le fichier
	cmd3->next = NULL;

	// Initialisation de t_exec
	exec->cmd_list = cmd1;
	exec->env = env;
	exec->pipes = NULL;
	exec->nb_cmd = 0;
	exec->last_exit = 0;
	exec->gc = gc;

	// Lancement des pipes
	run_pipes(exec);
	printf("Last exit: %d\n", exec->last_exit);

	gc_destroy(gc);
	return (0);
}
