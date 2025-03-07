/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:56 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 17:17:30 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

// TODO expand args[argc]
int	builtin_unset(const char **args, int argc, t_hmap *env)
{
	while (argc--)
		hmap_unset(env, args[argc]);
	return (EXIT_SUCCESS);
}
