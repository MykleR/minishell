/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:25 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/17 16:05:52 by thomarna         ###   ########.fr       */
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

void	export_env(t_hm *h, char *key, char *value)
{
	if (!value)
		hm_set(h, key, &((char *){ft_strdup("")}));
	else
		hm_set(h, key, &((char *){ft_strdup(value)}));
}

static inline uint32_t	hm_query(t_hm *h, const char *key,
							t_collection **keys, t_collection **vals)
{
	uint32_t		index;

	index = hash(key, ft_strlen(key)) & (h->cap - 1);
	*keys = &(((t_hm_bucket *)h->data) + index)->keys;
	*vals = &(((t_hm_bucket *)h->data) + index)->values;
	index = 0;
	while (index < (*keys)->len && ft_strcmp(
			*((char **)(*keys)->data + index), key))
		index++;
	return (index);
}

void	hm_del(t_hm *h, const char *key)
{
	t_collection	*vals;
	t_collection	*keys;
	uint32_t		index;

	if (__builtin_expect(!h || !key, 0))
		return ;
	index = hm_query(h, key, &keys, &vals);
	if (index < vals->len)
	{
		collection_remove(vals, index);
		collection_remove(keys, index);
	}
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
