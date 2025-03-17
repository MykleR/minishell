/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:26:50 by mykle             #+#    #+#             */
/*   Updated: 2025/03/17 17:51:41 by mykle            ###   ########.fr       */
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

	status = EXIT_SUCCESS;
	if (!argc)
		collection_iter(env, NULL, (t_iter_callb)__env_print_ex);
	while (argc--)
		if (!args[argc] || !args[argc][0]
			|| args[argc][0] == '='
			|| (args[argc][match_ident(args[argc])] != '='
			&& args[argc][match_ident(args[argc])] != '\0')
			|| insert_env(env, args[argc]))
			status = error(E_IDENTIF, "export", args[argc]);
	return (status);
}
