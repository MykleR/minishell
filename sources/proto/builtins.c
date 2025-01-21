/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:25 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/21 15:38:01 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "collection.h"
#include "libft.h"
#include "libft_string.h"
#include "proto.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
}

/* void	ft_env(t_env *env) */
/* { */
/* 	while (env->next != NULL && env) */
/* 	{ */
/* 		printf("%s\n", env->value); */
/* 		env = env->next; */
/* 	} */
/* 	if (env) */
/* 		printf("%s\n", env->value); */
/* } */

char	*get_key(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, i+1);
	return (dest);
}

char	*get_value(char *src)
{
	char	*dest;

	dest = ft_strtrim(ft_strrchr(src, '='), "=");
	return (ft_strdup(dest));
}

void	init_env(char **ep, t_collection *c)
{
	hm_create(c, 2);
	while (*ep)
	{
		hm_set(c, get_key(*ep), get_value(*ep));
		ep++;
	}
}

int	main(int ac, char **av, char **ep)
{
	t_collection	c;

	init_env(ep, &c);
	printf("%s\n", (char *)hm_get(&c, "PATH"));
	hm_set(&c, "PATH", ft_strdup("graou"));
	printf("%s\n", (char *)hm_get(&c, "PATH"));
	(void)ac;
	(void)av;
}
