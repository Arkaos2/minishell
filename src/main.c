/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:23:55 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/25 19:00:15 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	readline_check(t_envp *env)
{
	char	*input;
	t_envp *head = env;

	while(1)
	{
		env = head;
		input = readline("minishell: ");
		if (!input)
			break;
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		if (!is_whitespace(input))
			add_history(input);
		else
			continue;
		free(input);
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	t_envp *env = create_envp(envp);
	if(argc != 1)
		return 0;
	readline_check(env);
	return 0;
}
