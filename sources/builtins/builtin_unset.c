/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:56 by mykle             #+#    #+#             */
/*   Updated: 2025/03/12 14:45:25 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

// TODO expand args[argc]
int	builtin_unset(const char **args, int argc, t_hmap *env)
{
	while (argc--)
	{
		if (ft_strcmp(args[argc], "?") != 0)
			hmap_unset(env, args[argc]);
	}
	return (EXIT_SUCCESS);
}
