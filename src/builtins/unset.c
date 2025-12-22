/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:02:37 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/22 16:42:06 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_unset(t_cmd *cmd, t_envp *env, t_gc)
{
	while(env)
	{
		if(ft_strcmp(env->key, cmd->args[1]))
		
	}
}
