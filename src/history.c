/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:23:51 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/14 15:53:15 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (!(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			return (0);
		i++;
	}
	return (1);
}

int	readline_check(t_envp *env)
{
	char	*input;

	while (1)
	{
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
		if(ft_strncmp("env", input, 3) == 0)
		{
			while(env->next != NULL)
			{
				printf("%s%s\n", env->key, env->value);
				env = env->next;
			}
		}
		free(input);
	}
	return (1);
}
