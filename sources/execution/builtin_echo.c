/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:09 by mykle             #+#    #+#             */
/*   Updated: 2025/03/19 05:36:31 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static int	check_option(const char *arg)
{
	if (arg[0] != '-')
		return (0);
	while (*++arg)
		if (*arg != 'n')
			return (0);
	return (1);
}

int	builtin_echo(const char **argv, int argc, t_hmap *env)
{
	bool	nl;
	int		i;

	(void)env;
	i = 0;
	while (i < argc && argv[i] && check_option(argv[i]))
		i++;
	nl = i > 0;
	while (i < argc)
	{
		ft_putstr_fd((char *)argv[i], STDOUT_FILENO);
		if (i < argc - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
