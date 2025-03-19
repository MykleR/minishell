/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:38:50 by mykle             #+#    #+#             */
/*   Updated: 2025/03/19 14:21:18 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Try to execute a command with the given path
 * Returns nothing if successful (process is replaced), continues if failed
 */
static void	try_execute(const char *path, const char **args,
				char **envp, bool is_dir)
{
	struct stat	buf;

	if (is_dir && access(path, F_OK | X_OK) != 0)
	{
		if (errno == EACCES)
			exit(error(E_ERROR, args[0]) * 126);
		exit(error(E_ERROR, args[0]) * 127);
	}
	if (!is_dir && access(path, F_OK) != 0)
		return ;
	if (stat(path, &buf) == 0 && S_ISDIR(buf.st_mode))
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
static void	try_path_dirs(const char **args, char *path, char **envp)
{
	char	*dir;

	dir = ft_strtok(path, ":");
	while (dir)
	{
		try_path_dir(dir, args, envp);
		dir = ft_strtok(NULL, ":");
	}
}

int	exec_path(const char **args, t_hmap *env)
{
	char	**path;
	char	**envp;

	if (!args || !args[0] || !*args[0])
		exit(error(E_NOTCMD, args[0]) * 127);
	path = hmap_get(env, "PATH");
	if (!path)
		path = &(char *){"./"};
	envp = env_to_array(env);
	if (!ft_strchr(args[0], '/'))
		try_path_dirs(args, *path, envp);
	else
		try_execute(args[0], args, envp, true);
	exit(error(E_NOTCMD, args[0]) * 127);
}
