/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:25 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/11 17:49:08 by thomarna         ###   ########.fr       */
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

// get_env > builtins env (Need fnct features to list hashmap)

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
	ft_strlcpy(dest, src, i + 1);
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
	hm_create(c, 2, sizeof(char **), (t_clear_info){alloc_f, T_HEAP});
	while (*ep)
	{
		/* printf("%s=%s\n", get_key(*ep), get_value(*ep)); */
		hm_set(c, get_key(*ep), get_value(*ep));
		ep++;
	}
}

void	str_print(void *ptr, void *arg)
{
	(void)arg;
	ft_printf("%s, ", *(char **)ptr);
}

void	env_iter(t_hm *h, void *arg, void (*iter)(const char *, const char *,
			void *))
{
	uint32_t		i;
	t_collection	*keys;
	t_collection	*vals;
	uint32_t		j;

	i = 0;
	j = 0;
	if (!h || !h->data)
		return ;
	while (i < h->cap)
	{
		keys = &(((t_hm_bucket *)h->data) + i)->keys;
		vals = &(((t_hm_bucket *)h->data) + i)->values;
		j = 0;
		while (j < keys->len)
		{
			iter(*((char **)keys->data + j), vals->data + vals->mem * j, arg);
			j++;
		}
		i++;
	}
	return ;
}

void	get_env(const char *key, const char *value, void *arg)
{
	(void)arg;
	printf("%s=%s\n", key, value);
}

int	main(int ac, char **av, char **ep)
{
	t_collection	c;

	init_env(ep, &c);
	/* printf("%s\n", (char *)hm_get(&c, "PATH")); */
	/* hm_set(&c, "PATH", ft_strdup("graou")); */
	/* printf("%s\n", (char *)hm_get(&c, "PATH")); */
	env_iter(&c, NULL, get_env);
	(void)ac;
	(void)av;
}
