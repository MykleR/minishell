/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:50 by mykle             #+#    #+#             */
/*   Updated: 2025/03/12 14:40:28 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft_string.h"
#include <execution.h>

int builtin_export(const char **args, int argc, t_hmap *env)
{
	(void)env;
	if (argc == 0)
	{
		printf("Export list here\n");
		return (EXIT_SUCCESS);
	}
	else
	{
		while (argc--)
		{
			printf("%s\n", ft_strtrim(args[argc], "="));
		}
	}
	printf("nb args: %d\n", argc);
	while (argc--)
		printf("%s\n", args[argc]);
	return (0);
}
