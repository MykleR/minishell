/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:08:10 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/13 13:12:34 by thomarna         ###   ########.fr       */
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
	hm_create(c, 2, sizeof(char **), (t_clear_info){alloc_f, T_HEAP});
	while (*ep)
	{
		hm_set(c, get_key(*ep), &((char *){ft_strdup(get_value(*ep))}));
		ep++;
	}
}

static void	print_env(void *ptr, void *arg)
{
	(void)arg;
	ft_printf("%s=%s\n", *(char **)ptr, *(char **)hm_get(arg, *(char **)ptr));
}

void	get_env(t_hm *h)
{
	t_collection	*keys;

	keys = &(((t_hm_bucket *)h->data))->keys;
	collection_iter(keys, h, print_env);
}
