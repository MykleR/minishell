/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:09 by mykle             #+#    #+#             */
/*   Updated: 2025/03/12 01:13:22 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	builtin_echo(const char **argv, int argc, t_hmap *env)
{
	bool	nl;
	int		i;

	(void)env;
	nl = argc >= 1 && argv[0] && !ft_strcmp(argv[0], "-n");
	i = -1 + nl;
	while (++i < argc)
	{
		ft_putstr_fd((char *)argv[i], STDOUT_FILENO);
		if (i < argc - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
