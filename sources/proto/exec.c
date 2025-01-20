/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:02:25 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/20 16:29:11 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"
#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
//REW0RK NEED With real signals (126, 127 toussa toussa)
int	err0r(char *cmd)
{
	char	**str;

	str = ft_split(cmd, ' ');
	if (str[0])
	{
		if (errno == 14)
			ft_dprintf(2, "%s: command not found\n", str[0]);
		else
			ft_dprintf(2, "pipex: %s: %s\n", str[0], strerror(errno));
	}
	else
	{
		if (errno == 14)
			ft_dprintf(2, " : command not found\n");
		else
			ft_dprintf(2, "pipex: %s\n", strerror(errno));
	}
	free_split(str);
	return (1);
}


//NEED REWORK WITH COLLECTIONs ???
//HashMap au lieu de char**ep (Dependra du parsing des envars avec les builtins ect.. )
char	*get_path(char **ep, char *cmd)
{
	char	**paths;
	char	*tmp;
	char	*path;
	int		i;

	i = -1;
	while (*ep && ft_strnstr(*ep, "PATH", 4) == 0)
		ep++;
	if (!*ep)
		return (NULL);
	paths = ft_split(*ep + 5, ':');
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
	}
	free_split(paths);
	return (0);
}

int	execmd(char **ep, char *av)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(av, ' ');
	if (cmds == NULL)
		err0r("");
	if (access(cmds[0], F_OK | X_OK) == 0)
		path = cmds[0];
	else
		path = get_path(ep, cmds[0]);
	if (path == NULL)
	{
		free_split(cmds);
		return (1);
	}
	execve(path, cmds, ep);
	free(path);
	free_split(cmds);
	return (1);
}
