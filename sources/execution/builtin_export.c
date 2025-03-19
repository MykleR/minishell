/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:50 by mykle             #+#    #+#             */
/*   Updated: 2025/03/19 03:41:35 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	insert_env(t_hmap *env, const char *arg)
{
	char	*key;
	char	*value;

	if (!ft_strchr(arg, '='))
	{
		if (!hmap_get(env, arg))
			hmap_set(env, arg, &(char *){NULL});
		return (EXIT_SUCCESS);
	}
	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_strdup(ft_strchr(arg, '=') + 1);
	hmap_set(env, key, &value);
	alloc_f(key);
	return (EXIT_SUCCESS);
}

int	builtin_export(const char **args, int argc, t_hmap *env)
{
	int	status;
	int	i;

	if (!argc)
		collection_iter(env, NULL, (t_iter_callb)__env_print_ex);
	status = EXIT_SUCCESS;
	i = -1;
	while (++i < argc)
	{
		if (!args[i] || !args[i][0] || args[i][0] == '='
			|| (args[i][check_ident(args[i])] != '='
			&& args[i][check_ident(args[i])] != '\0')
			|| insert_env(env, args[i]))
			status = error(E_IDENTIF, "export", args[i]);
	}
	return (status);
}
