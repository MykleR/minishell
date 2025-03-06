/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:27:31 by mykle             #+#    #+#             */
/*   Updated: 2025/03/06 01:16:34 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static int	cd_var(t_hm *env, const char *var_name)
{
	char	*var;

	var = hm_get(env, var_name);
	if (var)
		return (builtin_cd(*(char **)var, env));
	ft_dprintf(STDERR_FILENO, "cd: %s not set\n", var_name);
	return (EXIT_FAILURE);
}

int	builtin_pwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX))
	{
		ft_printf("%s\n", buffer);
		return (EXIT_SUCCESS);
	}
	ft_dprintf(STDERR_FILENO, "pwd: %s\n", strerror(errno));
	return (EXIT_FAILURE);
}

int	builtin_cd(char *path, t_hm *env)
{
	char	*cwd;
	char	buffer[PATH_MAX];

	if (!path || !*path || !ft_strcmp(path, "~"))
		return (cd_var(env, "HOME"));
	if (!ft_strcmp(path, "-"))
		return (cd_var(env, "OLDPWD"));
	cwd = getcwd(buffer, PATH_MAX);
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		return (EXIT_FAILURE);
	}
	hm_set(env, "PWD", &((char *){ft_strdup(path)}));
	hm_set(env, "OLDPWD", &((char *){ft_strdup(cwd)}));
	return (EXIT_SUCCESS);
}
