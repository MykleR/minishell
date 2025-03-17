/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:27:31 by mykle             #+#    #+#             */
/*   Updated: 2025/03/17 18:19:54 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static int	cd_var(t_hmap *env, const char *var_name)
{
	char	*var;

	var = hmap_get(env, var_name);
	if (var)
		return (builtin_cd((const char **)var, 1, env));
	return (error(E_NOTSET, "cd", var_name));
}

int	builtin_cd(const char **argv, int argc, t_hmap *env)
{
	char		*cwd;
	char		buffer[PATH_MAX];

	if (argc > 1)
		return (error(E_TOOMANY, "cd"));
	if (!argc)
		return (cd_var(env, "HOME"));
	if (!ft_strcmp(argv[0], "-"))
		return (cd_var(env, "OLDPWD"));
	cwd = getcwd(buffer, PATH_MAX);
	if (chdir(argv[0]) == E_ERROR)
		return (error(E_OPEN, "cd", argv[0], strerror(errno)));
	hmap_set(env, "OLDPWD", &((char *){ft_strdup(cwd)}));
	cwd = getcwd(buffer, PATH_MAX);
	hmap_set(env, "PWD", &((char *){ft_strdup(cwd)}));
	return (EXIT_SUCCESS);
}
