/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:23:51 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/03 20:05:57 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_command(char *input, char *cmd)
{
	if (!input || !cmd)
		return (0);
	while (*input && ft_is_whitespace(*input))
		input++;
	while (*cmd && *input && *input == *cmd)
	{
		input++;
		cmd++;
	}
	// if cmd not fully matched -> not the same command
	if (*cmd != '\0')
		return (0);
	// skip all whitespace after command and ensure nothing else follows
	while (*input && ft_is_whitespace(*input))
		input++;
	if (*input == '\0')
		return (1);
	return (0);
}

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

static void	print_env(t_envp *env)
{
	while (env != NULL)
	{
		if (env->key)
		{
			if (env->value)
				ft_fprintf(1, "%s=%s\n", env->key, env->value);
			else
				ft_fprintf(1, "%s=\n", env->key);
		}
		env = env->next;
	}
}

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
		if (ft_is_command(input, "env"))
			print_env(env);
		free(input);
	}
	return (1);
}
