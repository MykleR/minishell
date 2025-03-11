/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:25 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/11 17:59:15 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection.h"
#include "libft.h"
#include "libft_string.h"
#include "proto.h"
#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

//Need to rework pwd (add protec)
void	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
}

/* int	main(int ac, char **av, char **ep) */
/* { */
/* 	t_collection	c; */
/*  */
/* 	(void)ac; */
/* 	(void)av; */
/* 	init_env(ep, &c); */
/* 	printf("%s\n", *(char **)hm_get(&c, "PATH")); */
/* 	hm_del(&c, "PATH"); */
/* 	env_builtin(&c); */
/* } */
