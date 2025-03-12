/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:50 by mykle             #+#    #+#             */
/*   Updated: 2025/03/12 21:29:48 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft_string.h"
#include <execution.h>

static void	insert_env(t_hmap *env, const char *arg)
{
	char	*key;
	char	*value;

	if (!ft_strchr(arg, '='))
	{
		if (!hmap_get(env, arg))
			hmap_set(env, arg, &(char *){NULL});
		return ;
	}
	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_strdup(ft_strchr(arg, '=') + 1);
	hmap_set(env, key, &value);
	alloc_f(key);
}

int	builtin_export(const char **args, int argc, t_hmap *env)
{
	if (!argc)
	{
		collection_iter(env, NULL, (t_iter_callb)__env_print_ex);
		return (EXIT_SUCCESS);
	}
	while (argc--)
	{
		if (!args[argc] || !args[argc][0] || args[argc][0] == '=')
			return (error(E_IDENTIF, "export", args[argc]));
		insert_env(env, args[argc]);
	}
	return (EXIT_SUCCESS);
}
