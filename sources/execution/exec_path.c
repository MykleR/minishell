/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:38:50 by mykle             #+#    #+#             */
/*   Updated: 2025/03/14 06:18:25 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Try to execute a command with the given path
 * Returns nothing if successful (process is replaced), continues if failed
 */
static void	try_execute(const char *cmd_path, char **args, char **envp)
{
	struct stat	buf;

	if (access(cmd_path, F_OK) != 0)
		return ;
	if (stat(cmd_path, &buf) == 0 && S_ISDIR(buf.st_mode))
		exit(error(E_ISDIR, args[0]) * 126);
	if (access(cmd_path, X_OK) == 0)
		execve(cmd_path, args, envp);
}

/**
 * Construct full path and try to execute the command
 */
static void	try_path_dir(const char *dir, char **args, char **envp)
{
	char	full_path[PATH_MAX];

	ft_strlcpy(full_path, dir, PATH_MAX);
	if (ft_strlen(dir) > 0 && dir[ft_strlen(dir) - 1] != '/')
		ft_strlcat(full_path, "/", PATH_MAX);
	ft_strlcat(full_path, args[0], PATH_MAX);
	try_execute(full_path, args, envp);
}

/**
 * Try each directory in PATH environment variable
 */
static void	try_path_dirs(char **args, t_hmap *env, char **envp)
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

int	exec_path(char **args, t_hmap *env)
{
	char	**envp;

	if (!args || !args[0])
		return (EXIT_FAILURE);
	envp = env_to_array(env);
	if (ft_strncmp(args[0], "/", 1) && ft_strncmp(args[0], "./", 2))
		try_path_dirs(args, env, envp);
	try_execute(args[0], args, envp);
	alloc_f(envp);
	exit(error(E_NOTCMD, args[0]) * 127);
}
