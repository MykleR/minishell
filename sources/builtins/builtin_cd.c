/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:27:31 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 03:54:27 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static int	cd_var(t_hmap *env, const char *var_name)
{
	char	*var;

	var = hmap_get(env, var_name);
	if (var)
		return (builtin_cd((const char **)var, 1, env));
	return (error(E_NOENV, "cd", var_name));
}

int	builtin_cd(const char **args, int argc, t_hmap *env)
{
	const char	*path;
	char		*cwd;
	char		buffer[PATH_MAX];

	if (argc > 1)
		return (error(E_TOO_MANY, "cd"));
	path = args[0];
	if (!path || !*path)
		return (cd_var(env, "HOME"));
	if (!ft_strcmp(path, "-"))
		return (cd_var(env, "OLDPWD"));
	cwd = getcwd(buffer, PATH_MAX);
	if (chdir(path) == E_ERROR)
		return (error(E_OPEN, "cd", path, strerror(errno)));
	hmap_set(env, "OLDPWD", &((char *){ft_strdup(cwd)}));
	cwd = getcwd(buffer, PATH_MAX);
	hmap_set(env, "PWD", &((char *){ft_strdup(cwd)}));
	return (EXIT_SUCCESS);
}
