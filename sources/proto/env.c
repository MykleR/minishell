/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:57:40 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/17 16:03:13 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "proto.h"

char *get_env(t_hm *h, char *key)
{
	return(ft_strdup(hm_get(h, key)));
}

/* int	main(int ac, char **av, char **ep) */
/* { */
/* 	char *str; */
/* 	(void)ac; */
/* 	(void)av; */
/* 	t_collection c; */
/* 	init_env(ep, &c); */
/* 	str = get_env(&c, "OLD"); */
/* 	printf("%s\n", *((char **)str)); */
/* } */
