/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:45 by mykle             #+#    #+#             */
/*   Updated: 2025/03/13 06:37:01 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	builtin_exit(const char **args, int argc, t_hmap *env)
{
	int64_t	exit_code;

	(void)env;
	exit_code = 0;
	ft_printf("exit\n");
	if (argc && args[0] && !ft_safe_atoi64(args[0], &exit_code))
	{
		error(E_NUMERIC, "exit", args[0]);
		exit(2);
	}
	if (argc <= 1)
		exit(exit_code);
	return (error(E_TOOMANY, "exit"));
}
