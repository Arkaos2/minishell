/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:30:46 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/16 17:41:32 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_struct(void)
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
	shell->gc = gc;
	return (shell);
}

int main(void)
{
    char    *line;
    t_shell *shell;
    t_token *tok;
    t_cmd   *cmd;
    t_redir *r;

    while (1)
    {
        line = readline("minishell: ");
        if (!line)
            break ;

        if (*line)
            add_history(line);

        // --- NOUVEAU GC POUR CETTE LIGNE ---
        shell = init_struct();
        if (!shell)
        {
            perror("init_struct");
            exit(1);
        }

        // --- LEXING ---
        ultime_lexing(&shell->tok, line, shell->gc);
		if (!shell->tok)
		{
			puts("yep");
			gc_destroy(shell->gc);
			free(line);
			exit(1);
		}

        // --- FILLER : CMD, ARGS, REDIRS ---
        ultime_filler(shell);

        // ----- DEBUG TOKENS -----
        puts("=====TOKEN======");
        tok = shell->tok;
        while (tok)
        {
            printf("[%u] %s\n", tok->type, tok->value);
            tok = tok->next;
        }

        // ----- DEBUG COMMANDES -----
        cmd = shell->cmd;
        while (cmd)
        {
            puts("===== CMD =====");
            for (size_t i = 0; cmd->args && cmd->args[i]; i++)
                printf("arg[%zu] = %s\n", i, cmd->args[i]);

            // Redirections
            r = cmd->redirs;
            while (r)
            {
                printf("[%u] %s\n", r->type, r->file);
                r = r->next;
            }

            cmd = cmd->next;
        }

        // Libération complète
        gc_destroy(shell->gc);
        free(line);
    }
    return (0);
}

// int	main(int ac, char **av)
// {
// 	t_shell	*shell;
// 	t_token	*tmp;
// 	t_cmd	*cur;
// 	t_redir	*r;

// 	if (ac != 2)
// 		return (0);
// 	shell = init_struct();
// 	if (!shell)
// 	{
// 		gc_destroy(shell->gc);
// 		perror("minishell:");
// 		exit(ENOMEM);
// 	}
// 	ultime_lexing(&shell->tok, av[1], shell->gc);
// 	ultime_filler(shell);
// 	puts("=====TOKEN======");
// 	tmp = shell->tok;
// 	while (tmp)
// 	{
// 		printf("[%u] %s\n", tmp->type, tmp->value);
// 		tmp = tmp->next;
// 	}
// 	cur = shell->cmd;
// 	while (cur)
// 	{
// 		printf("===== CMD =====\n");
// 		for (size_t i = 0; cur->args[i]; i++)
// 			printf("arg[%zu] = %s\n", i, cur->args[i]);
// 		r = cur->redirs;
// 		while (r)
// 		{
// 			printf("[%u] %s\n", r->type, r->file);
// 			r = r->next;
// 		}
// 		cur = cur->next;
// 	}
// 	gc_destroy(shell->gc);
// 	return (1);
// }
