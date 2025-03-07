/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:45 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 03:52:13 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	builtin_exit(const char **args, int argc, t_hmap *env)
{
	int64_t	exit_code;

	(void)env;
	if (argc > 1)
		return (error(E_TOO_MANY, "exit"));
	if (!argc || !args[0])
		exit(EXIT_SUCCESS);
	if (!ft_safe_atoi64(args[0], &exit_code))
	{
		error(E_NUMERIC, "exit", args[0]);
		exit(2);
	}
	exit((int)exit_code);
}
