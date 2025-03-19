/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:38:50 by mykle             #+#    #+#             */
/*   Updated: 2025/03/19 05:37:28 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Try to execute a command with the given path
 * Returns nothing if successful (process is replaced), continues if failed
 */
static void	try_execute(const char *path, const char **args,
				char **envp, bool dir)
{
	struct stat	buf;

	if (!dir && access(path, F_OK) != 0)
		return ;
	if (dir && access(path, F_OK) != 0)
		exit(error(E_ERROR, path) * 127);
	if (dir && stat(path, &buf) == 0 && S_ISDIR(buf.st_mode))
		exit(error(E_ISDIR, args[0]) * 126);
	if (access(path, X_OK) == 0)
		execve(path, (char **)args, envp);
}

/**
 * Construct full path and try to execute the command
 */
static void	try_path_dir(const char *dir, const char **args, char **envp)
{
	char	full_path[PATH_MAX];

	ft_strlcpy(full_path, dir, PATH_MAX);
	if (ft_strlen(dir) > 0 && dir[ft_strlen(dir) - 1] != '/')
		ft_strlcat(full_path, "/", PATH_MAX);
	ft_strlcat(full_path, args[0], PATH_MAX);
	try_execute(full_path, args, envp, false);
}

/**
 * Try each directory in PATH environment variable
 */
static void	try_path_dirs(const char **args, t_hmap *env, char **envp)
{
	char	**path_var;
	char	*path_copy;
	char	*dir;

	path_var = hmap_get(env, "PATH");
	if (!path_var || !*path_var)
		return ;
	path_copy = ft_strdup(*path_var);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		try_path_dir(dir, args, envp);
		dir = ft_strtok(NULL, ":");
	}
	alloc_f(path_copy);
}

int	exec_path(const char **args, t_hmap *env)
{
	char	**envp;
	bool	is_asbolute;

	if (!args || !args[0] || !*args[0])
		exit(error(E_NOTCMD, args[0]) * 127);
	envp = env_to_array(env);
	is_asbolute = ft_strchr(args[0], '/') != NULL;
	if (!is_asbolute)
		try_path_dirs(args, env, envp);
	try_execute(args[0], args, envp, is_asbolute);
	exit(error(E_NOTCMD, args[0]) * 127);
}
