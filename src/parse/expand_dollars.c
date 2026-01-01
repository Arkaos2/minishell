/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@example.com>                 +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:00:00 by automated         #+#    #+#             */
/*   Updated: 2025/12/22 20:00:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollars(t_shell *s, char *str)
{
    if (!s || !str)
        return (NULL);
    return (gc_strdup(s->gc, str));
}
