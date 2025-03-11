/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:08:10 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/11 17:58:50 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "proto.h"

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

	dest = ft_strtrim(ft_strchr(src, '='), "=");
	return (ft_strdup(dest));
}

void	init_env(char **ep, t_collection *c)
{
	hmap_init(c, 2, sizeof(char **), (t_clear_info){alloc_f, T_HEAP});
	hmap_set(c, "?", &((char *){ft_strdup("0")}));
	while (*ep)
	{
		hmap_set(c, get_key(*ep), &((char *){ft_strdup(get_value(*ep))}));
		ep++;
	}
}

static void	print_env(void *ptr, void *arg)
{
	(void)arg;
	ft_printf("%s=%s\n", *(char **)ptr, *(char **)hmap_get(arg, *(char **)ptr));
}

void	env_builtin(t_hmap *h)
{
	t_collection	*keys;

	keys = &(((t_hmap_bucket *)h->data))->keys;
	collection_iter(keys, h, print_env);
}
