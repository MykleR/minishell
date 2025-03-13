/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:10:22 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/13 06:19:01 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	builtin_env(const char **args, int argc, t_hmap *env)
{
	(void)args;
	(void)argc;
	collection_iter(env, NULL, (t_iter_callb)__env_print_ev);
	return (EXIT_SUCCESS);
}
