/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:45:48 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 17:24:20 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	builtin_pwd(const char **args, int argc, t_hmap *env)
{
	char	buffer[PATH_MAX];

	(void)args;
	(void)argc;
	(void)env;
	if (getcwd(buffer, PATH_MAX))
	{
		ft_printf("%s\n", buffer);
		return (EXIT_SUCCESS);
	}
	return (error(E_ERROR, "pwd"));
}
