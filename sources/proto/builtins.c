
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:25 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/12 09:49:20 by thomarna         ###   ########.fr       */
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

void	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
}

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
	return (ft_strdup(dest));
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
		/* printf("%s %s\n", get_key(*ep), get_value(*ep)); */
		hm_set(c, get_key(*ep), &((char *){ft_strdup(get_value(*ep))}));
		ep++;
	}
}

void	env_print(const char *key, t_collection *c)
{
	(void)c;
	printf("%s=%s\n", key, (char *)hm_get(c, key));
	printf("%s\n", key);
}
void	str_print(void *ptr, void *arg)
{
	(void)arg;
	ft_printf("%s %s\n", *(char **)ptr, *(char **)hm_get(arg, *(char **)ptr));
}

void	get_env(t_hm *h)
{
	t_collection *keys;
	keys = &(((t_hm_bucket *)h->data))->keys;
	collection_iter(keys, h, str_print);
}

int	main(int ac, char **av, char **ep)
{
	t_collection	c;

	init_env(ep, &c);
	/* printf("%s\n", (char *)hm_get(&c, "PATH")); */
	/* printf("%s\n", *(char **)hm_get(&c, "LS_COLORS")); */
	get_env(&c);
	(void)ac;
	(void)av;
}
