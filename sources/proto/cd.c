/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:50:58 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/17 16:42:47 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "proto.h"
#include <stdlib.h>
#include <unistd.h>

void	cd_hyphen(t_hm *h)
{
	char	*oldpwd;

	oldpwd = hm_get(h, "OLDPWD");
	if (oldpwd == NULL)
		printf("cd: OLDPWD not set\n");
	else if (!chdir(oldpwd))
		hm_set(h, "PWD", &((char *){ft_strdup(oldpwd)}));
	else
	{
		printf("cd: ");
		if (access(oldpwd, F_OK) == -1)
			printf("%s: No such file or directory\n", oldpwd);
		else if (access(oldpwd, R_OK) == -1)
			printf("%s: Permission denied\n", oldpwd);
		else
			printf("%s: Not a directory\n", oldpwd);
	}
}

void	change_dir(char *path, t_hm *h)
{
	char	*cwd;
	char	buffer[4096];

	cwd = getcwd(buffer, 4096);
	if (!chdir(path))
		hm_set(h, "OLDPWD", &((char *){ft_strdup(cwd)}));
	else if (ft_strncmp(path, "-", 1) == 0)
		cd_hyphen(h);
	else
	{
		printf("cd: ");
		if (access(path, F_OK) == -1)
			printf("%s: No such file or directory\n", path);
		else if (access(path, R_OK) == -1)
			printf("%s: Permission denied\n", path);
		else
			printf("%s: Not a directory\n", path);
	}
}

int	main(int ac, char **av, char **ep)
{
	t_collection	c;

	(void)ac;
	(void)av;
	init_env(ep, &c);
	change_dir("-", &c);
	printf("OLDPWD: %s\nPWD:", *(char **)hm_get(&c, "OLDPWD"));
	ft_pwd();
}
