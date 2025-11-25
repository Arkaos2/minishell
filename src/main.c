/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:23:55 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/25 15:26:40 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_list(t_envp *envp)
{
	
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
